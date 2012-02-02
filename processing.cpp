//------------------------------------------------------------------------------
// Модуль реализует ф-ции работы с переменными настройки и алгоритм
// вычисления измеряемых величин
//------------------------------------------------------------------------------
extern "C"{
#include "variables.h"
#include "board.h"
#include "timers.h"
#include "messages.h"
#include "thermocouple.h"
#include "adc_fsm.h"
};

//#include "msg.h"
#include <math.h>
#include "processing.h"

const float d_c = 1.0 / 123.0;

//------------------------------------------------------------------------------
float Clapp(T_CLAPP *clapp, float x)
{                                                    
  float a, b;
 /*                //HERESY
  for(int i = 1; i < 5; i++)
    if(((x >= clapp->x[i]) && (x < clapp->x[i + 1])) || 
       ((i == 0) && (x < clapp->x[0])) || 
         ((i == 5) && (x >= clapp->x[5])))
    {
      a = (clapp->y[i + i] - clapp->y[i]) / (clapp->x[i + 1] - clapp->x[i]);
      b = clapp->y[i] - a * clapp->x[i];
    };
  return a * x + b;
  */
  
  if(x < clapp->x[0])
    return clapp->y[0];
  for(char i = 0; i < 5; i ++)
    if((x >= clapp->x[i]) && (x < clapp->x[i + 1]))
    {
      a = (clapp->y[i + 1] - clapp->y[i]) / (clapp->x[i + 1] - clapp->x[i]);
      b = clapp->y[i] - a * clapp->x[i];
      return a * x + b;
    };
  if(x >= clapp->x[5])
    return clapp->x[5];
  return 0.0;
};
//------------------------------------------------------------------------------

void ChannelTemp::Init()
{
   code_t = 0.0;
  t_cl_e = 0.0;
  cel_f_t_1 = cel_f_t = 0.0;
  mi_d_t_ = 0.0;
  mi_d_t_1 = 0.0;  
  mism_t_1 = 0.0;
  l_comp_t = 0.0;
  
  t_f_t = 1.0;                                                                   /// wtf
  
  cel_f_t = 123.456;                                                             // wtf
}

void ChannelTemp::LoadVariables()
{
  if(!getDictLocked())
  {
    // Init();
    if(side == LEFT_CH)
    {
      code_t = GetIntValueByTag(ADC_1);
    }
    else
    {
      code_t = GetIntValueByTag(ADC_3);
    };
    t_cl_e = GetFloatValueByTag(T_CL_E);
    //--------------------------------------------
    //Loading NVRAM variables
    //float
    shift_t = GetIntValueByTag(base_temp + SHIFT_T); 
    k_cd_t = GetFloatValueByTag(base_temp + K_CD_T);
    t_f_t = GetFloatValueByTag(base_temp + T_F_T);
    adj_s_t = GetFloatValueByTag(base_temp + ADJ_S_T);
    k_p_t = GetFloatValueByTag(base_temp + K_P_T);
    k_d_t = GetFloatValueByTag(base_temp + K_D_T);
    t_df_t = GetFloatValueByTag(base_temp + T_DF_T);
    ki_t = GetFloatValueByTag(base_temp + KI_T);
    disp_t = GetFloatValueByTag(base_temp + DISP_T);
    sm_t = GetFloatValueByTag(base_temp + SM_T);
    k_clc_t = GetFloatValueByTag(base_temp + K_CLC_T);
    //int
    lim_lo_t = GetIntValueByTag(base_temp + LIM_LO_T);
    lim_hi_t = GetIntValueByTag(base_temp + LIM_HI_T); 
  };
  RefreshVariables();
}

void ChannelTemp::RefreshVariables()
{
//  k_f_t = exp(-d_c/t_f_t);
 // k_df_t = exp(-d_c/t_df_t);
  
  k_df_t_1 = d_c/(d_c + t_df_t);
  k_df_t_2 = t_df_t/(d_c + t_df_t);
}

void ChannelTemp::Process()
{
  if(!tempFault)
  {
    //step 1
   // cd_sh_t = code_t + shift_t * 1.0e-3;
    //step 2
  //  u_t = cd_sh_t * k_cd_t * 1.0e-6;
    
    //step 1, 2
    u_t = (code_t + shift_t) * k_cd_t * 1.0e-3;
 
    t_t = mvToTemp(u_t);
    //step 3
   
    cel_t = t_t + t_cl_e;
    //step 4
    //k_f_t = exp(-d_c/t_f_t);
    //cel_f_t = k_f_t * (cel_f_t_1 - cel_t) + cel_t; 
    
    cel_f_t = (cel_t * d_c +  cel_f_t_1 * t_f_t) / (t_f_t + d_c);
    
    //step 5
    mism_t = adj_s_t - cel_f_t;
    //step 6
    mi_p_t = mism_t * k_p_t; 
    //step 7
    // k_df_t = exp(-d_c/t_df_t);
    
    mi_d_t_ = k_df_t_1 * mism_t + k_df_t_2 * mi_d_t_1;
    mi_d_t = mism_t - mi_d_t_;  
    //step 8
    mi_kd_t = mi_d_t * k_d_t;
    //step 9
    sk_int_t = ki_t * mism_t / ( 1 + disp_t * mism_t * mism_t);
    //step 10
    l_comp_t = l_comp_t + sk_int_t;
    //--------------------------------
    if(l_comp_t > 10000.0) l_comp_t = 10000.0;
    if(l_comp_t < -10000.0) l_comp_t = -10000.0;
    //--------------------------------
    //step 11
    mi_dc_t = mi_kd_t + mi_p_t + l_comp_t + sm_t;
    //step 12
    clc_sh_t = k_clc_t * mi_dc_t;
    //step 14
    clc_li_t = (int)clc_sh_t;
    if(clc_sh_t < lim_lo_t)
    {
      clc_li_t = lim_lo_t;
      l_comp_t = 0;
    };
    if(clc_sh_t > lim_hi_t)
    {
      clc_li_t = lim_hi_t;
      l_comp_t = 0;
    }; 
  };
  //-----------------------------
  cel_f_t_1 = cel_f_t;
  mi_d_t_1 = mi_d_t_;
//  mism_t_1 = mism_t;                                                             //do not want
};

void ChannelTemp::SaveResults()
{  
  if(!getDictLocked())
  {
    SetFloatValueByTag(base_temp + CEL_F_T, cel_f_t);
    SetFloatValueByTag(base_temp + CEL_T, cel_t);

    SetIntValueByTag(base_temp + CLC_LI_T, clc_li_t);
    SetFloatValueByTag(base_temp + U_T, u_t);
    SetFloatValueByTag(base_temp + T_T, t_t);
    
    SetFloatValueByTag(base_temp + MISM_T, mism_t);
    
    SetFloatValueByTag(base_temp + MI_DC_T, mi_dc_t);
    SetFloatValueByTag(base_temp + SK_INT_T, sk_int_t);
    SetFloatValueByTag(base_temp + L_COMP_T, l_comp_t);
    SetFloatValueByTag(base_temp + MI_P_T, mi_p_t);
    SetFloatValueByTag(base_temp + MI_KD_T, mi_kd_t);
  };
};
//------------------------------------------------------------------------------

void ChannelO2::LoadVariables()
{
  if(!getDictLocked())
  {
    /*
    if(side == LEFT_CH)
    base = BASE_O2_L;
  else
    base = BASE_O2_R;
    */
    if(side == LEFT_CH)
    {
      code_e = GetIntValueByTag(ADC_2);
      /*    range = GetIntValueByTag(RANGE_O2_L);
      switch(range)
      {
    case 0:
    case 1:
      min = GetFloatValueByTag(MIN1_O2_L);
      max = GetFloatValueByTag(MIN1_O2_L);
      break;
    case 2:
      min = GetFloatValueByTag(MIN2_O2_L);
      max = GetFloatValueByTag(MIN2_O2_L);
      break;
    case 3:
      min = GetFloatValueByTag(MIN3_O2_L);
      max = GetFloatValueByTag(MIN3_O2_L);
      break;
      default:
      min = GetFloatValueByTag(MIN4_O2_L);
      max = GetFloatValueByTag(MIN4_O2_L);
      break;
    };*/
    }
    else
    {
      code_e = GetIntValueByTag(ADC_4);
      /*    range = GetIntValueByTag(RANGE_O2_R);
      switch(range)
      {
    case 0:
    case 1:
      min = GetFloatValueByTag(MIN1_O2_R);
      max = GetFloatValueByTag(MIN1_O2_R);
      break;
    case 2:
      min = GetFloatValueByTag(MIN2_O2_R);
      max = GetFloatValueByTag(MIN2_O2_R);
      break;
    case 3:
      min = GetFloatValueByTag(MIN3_O2_R);
      max = GetFloatValueByTag(MIN3_O2_R);
      break;
      default:
      min = GetFloatValueByTag(MIN4_O2_R);
      max = GetFloatValueByTag(MIN4_O2_R);
      break;
    };*/
    };
    
    //Loading NVRAM variables
    //int 
    //float
    shift_e = GetIntValueByTag(base_o2 + SHIFT_E);
    k_cd_e = GetFloatValueByTag(base_o2 + K_CD_E);
    t_f_e = GetFloatValueByTag(base_o2 + T_F_E);
    t_ff_t = GetFloatValueByTag(base_o2 + T_FF_T);
    t_f_o = GetFloatValueByTag(base_o2 + T_F_O);
    clapp_o2.x[0] = 0.0;
    clapp_o2.y[0] = 0.0;
    clapp_o2.x[1] = GetFloatValueByTag(base_o2 + X1);     
    clapp_o2.y[1] = GetFloatValueByTag(base_o2 + Y1);
    clapp_o2.x[2] = GetFloatValueByTag(base_o2 + X2);
    clapp_o2.y[2] = GetFloatValueByTag(base_o2 + Y2);
    clapp_o2.x[3] = GetFloatValueByTag(base_o2 + X3);
    clapp_o2.y[3] = GetFloatValueByTag(base_o2 + Y3);
    clapp_o2.x[4] = GetFloatValueByTag(base_o2 + X4);
    clapp_o2.y[4] = GetFloatValueByTag(base_o2 + Y4);
    clapp_o2.x[5] = GetFloatValueByTag(base_o2 + X5);
    clapp_o2.y[5] = GetFloatValueByTag(base_o2 + Y5);
    
  //  k_i_o = GetFloatValueByTag(base_o2 + K_I_O);
    //int
  //  sh_4_o = GetIntValueByTag(base_o2 + SH_4_O);  
    
    //RefreshVariables();
  };
};

void ChannelO2::SaveResults()
{
  if(!getDictLocked())
  {
    SetFloatValueByTag(base_temp + E_E, e_e); //debug tags is located in /temp/
    SetFloatValueByTag(base_o2 + C_KL_O, c_kl_o);
    SetFloatValueByTag(base_o2 + O2_1, c_f_o);
    
    if(side == LEFT_CH)
    {
    //  SetFloatValueByTag(CURR_O2_L, curr_o_o);
      SetFloatValueByTag(E_F_E_L, e_f_e);
    }
    else
    {
  //    SetFloatValueByTag(CURR_O2_R, curr_o_o);
      SetFloatValueByTag(E_F_E_R, e_f_e);
    };
   // SetIntValueByTag(base_o2 + CI_O_O, ci_o_o);
  };
}

void ChannelO2::RefreshVariables()
{
  k_f_e = exp(-d_c/t_f_e);
  k_ff_t = exp(-d_c / t_ff_t);
  k_f_o = exp(-d_c/t_f_o);
  
 // a = 16.0 / (max - min);
 // b = 20.0 - a * max;
}

void ChannelO2::Init()
{
  e_f_e_1 = 0;
  cel_ff_t_1 = 0;
  c_f_o_1 = 0;
}

void ChannelO2::Process()
{ 
  if  (1)     ///(!(tempFault || o2Fault))                                          temporary commented
  {  /*
    //step 1
    cd_sh_e = code_e + shift_e;
    //step 2
    e_e = cd_sh_e * k_cd_e * 1.0e-6;
    */
    
    e_e = (code_e + shift_e) * k_cd_e * 1.0e-3;
    
    //step 3
    //k_f_e = exp(-d_c/t_f_e);
    e_f_e = k_f_e * (e_f_e_1 - e_e) + e_e;
    //step 4
    if(e_f_e > 200.0)
      e_lf_e = 200.0;
    else
      e_lf_e = e_f_e;
    //step 5
    //k_ff_t = exp(-d_c / t_ff_t);
    cel_ff_t = k_ff_t * (cel_ff_t_1 - cel_f_t) + cel_f_t;
    //step 6  
    kel_ff_t = 273.16 + cel_ff_t;    
    //step 7
    den_o = -0.0216 * kel_ff_t; 
    //step 8
    ex_o = e_lf_e / den_o;
    //step 9
    c_o = exp(ex_o) * 20.67;
    //step 10
    //k_f_o = exp(-d_c/t_f_o);
    c_f_o = k_f_o * (c_f_o_1 - c_o) + c_o;
    //step 11
    c_kl_o = Clapp(&(clapp_o2), c_f_o);
  }
  else
  {
    c_kl_o = 0;
  };
  //step 12
 // curr_o_o = a * c_kl_o + b;
  
 // c_o_o = (int)(k_i_o * curr_o_o);
  //step 13
 // ci_o_o = c_o_o + sh_4_o;
  //-------------------------------------
  e_f_e_1 = e_f_e;
  cel_ff_t_1 = cel_ff_t;
  c_f_o_1 = c_f_o; 
}
//------------------------------------------------------------------------------
void ChannelHN::Init()
{
  e_f_h_1 = 0;
  e_ff_h_1 = 0;
  e_ffd_h_1 = 0;
  c_fd_h_1 = 0;
}

void ChannelHN::RefreshVariables()
{
  k_f_h = exp(-d_c / t_f_h);
  k_ff_h = exp(-d_c/t_ff_h);
  k_d_h = exp(-d_c / t_d_h);
  k_fd_h = exp(-d_c / t_fd_h);
  
 // a = 16.0 / (max - min);
 // b = 20.0 - a * max;
}

void ChannelHN::Process()
{
  if(!(tempFault || o2Fault))
  {
    //step 1
    //k_f_h = exp(-d_c / t_f_h);
    e_f_h = k_f_h * (e_f_h_1 - e_e) + e_e;
    //step 2
    //k_ff_h = exp(-d_c/t_ff_h);
    e_ff_h = k_ff_h * (e_ff_h_1 - e_f_h) + e_f_h;
    //step 3
    //k_d_h = exp(-d_c / t_d_h);
    /*
    t = k_d_h * (t_1 - e_ff_h) + e_ff_h;
    e_ffd_h = e_ff_h - t;
    */
    e_ffd_h_ = k_d_h * (e_ffd_h_1 - e_ff_h) + e_ff_h;
    e_ffd_h = e_ff_h - e_ffd_h_;
    //
    e_ffd_h_chuv_h = e_ffd_h * chuv_h;
    //step 4
    if(e_ffd_h < 0)
      d_ffd_h = k_l_h * e_ffd_h_chuv_h;
    else
      d_ffd_h = k_r_h * e_ffd_h_chuv_h;
    //step 5
    if(e_e < lim_h)
      e_li_h = 0;
    else
      e_li_h = klim_h * (e_e - lim_h);
    //step 6
    c_h = e_li_h + d_ffd_h;
    //step 7
    //k_fd_h = exp(-d_c / t_fd_h);
    c_fd_h = k_fd_h * (c_fd_h_1 - c_h) + c_h;
    //step 8
    c_kl_h = Clapp(&clapp_hn, c_fd_h);
  }
  else
  {
    c_kl_h = 0;
  };
  //step 9
 // curr_o_h = a * c_kl_h + b;
 // ci_h = (int)(k_i_h * curr_o_h);
  //step 10
 // ci_o_h = sh_4_h + ci_h;
  //---------------------------------------------------------
  e_f_h_1 = e_f_h;
  e_ff_h_1 = e_ff_h;
  e_ffd_h_1 = e_ffd_h_;
  c_fd_h_1 = c_fd_h;
  //  t_1 = t;
}

void ChannelHN::LoadVariables()
{
  if(!getDictLocked())
  {
    /*
    if(side == LEFT_CH)
    base = BASE_HN_L;
  else
    base = BASE_HN_R;
    */
    //Loading NVRAM variables
    t_f_h = GetFloatValueByTag(base_hn + T_F_H);
    t_ff_h = GetFloatValueByTag(base_hn + T_FF_H);
    t_d_h = GetFloatValueByTag(base_hn + T_D_H);
    k_r_h = GetFloatValueByTag(base_hn + K_R_H);
    k_l_h = GetFloatValueByTag(base_hn + K_L_H);
    lim_h = GetFloatValueByTag(base_hn + LIM_H);
    klim_h = GetFloatValueByTag(base_hn + KLIM_H);
    t_fd_h = GetFloatValueByTag(base_hn + T_FD_H);
    clapp_hn.x[0] = GetFloatValueByTag(base_hn + HN_X0); 
    clapp_hn.y[0] = GetFloatValueByTag(base_hn + HN_Y0);
    clapp_hn.x[1] = GetFloatValueByTag(base_hn + HN_X1);
    clapp_hn.y[1] = GetFloatValueByTag(base_hn + HN_Y1);
    clapp_hn.x[2] = GetFloatValueByTag(base_hn + HN_X2);
    clapp_hn.y[2] = GetFloatValueByTag(base_hn + HN_Y2);
    clapp_hn.x[3] = GetFloatValueByTag(base_hn + HN_X3);
    clapp_hn.y[3] = GetFloatValueByTag(base_hn + HN_Y3);
    clapp_hn.x[4] = GetFloatValueByTag(base_hn + HN_X4);
    clapp_hn.y[4] = GetFloatValueByTag(base_hn + HN_Y4);
    
    clapp_hn.x[5] = clapp_hn.x[4];
    clapp_hn.y[5] = clapp_hn.y[4];
    
    chuv_h = GetFloatValueByTag(base_hn + CHUV_HN);
  };
};

void ChannelHN::SaveResults()
{
  if(!getDictLocked())
  {
    SetFloatValueByTag(base_hn + C_KL_HN, c_kl_h);
    //SetIntValueByTag(base_hn + CI_O_H, ci_o_h);
    
    SetFloatValueByTag(base_temp + E_FF_D, c_fd_h);
    /*
    if(side == LEFT_CH)
    {  
      SetFloatValueByTag(CURR_H_L, curr_o_h);
    }
    else
    {
      SetFloatValueByTag(CURR_H_R, curr_o_h);
    }; */
  };
};

Processing::Processing(void)  //ctor
{
  leftTemp.SetSide(LEFT_CH);
  rightTemp.SetSide(RIGHT_CH);
  leftO2.SetSide(LEFT_CH);
  rightO2.SetSide(RIGHT_CH);
  leftHN.SetSide(LEFT_CH);
  rightHN.SetSide(RIGHT_CH);
  
  leftTemp.Init();
  rightTemp.Init();
  leftO2.Init();
  rightO2.Init();
  leftHN.Init();
  rightHN.Init();
};

void Processing::LoadVariables(void)
{
  leftTemp.LoadVariables();
  rightTemp.LoadVariables();
  leftO2.LoadVariables();
  rightO2.LoadVariables();
  leftHN.LoadVariables();
  rightHN.LoadVariables();
  
  leftTemp.RefreshVariables();
  rightTemp.RefreshVariables();
  leftO2.RefreshVariables();
  rightO2.RefreshVariables();
  leftHN.RefreshVariables();
  rightHN.RefreshVariables();
};

void Processing::Process(void)
{
//  if(GetMessage(MSG_VAR_CHANGED))
 // {
    LoadVariables();
 // };
}

void Processing::ProcessDSP(void)
{ 
 // setDebugPin();

  ProcessAdc(); 
  if(!getDictLocked())
  {
    leftTemp.setTempFault(GetIntValueByTag(FLT_TP_L));
  };
  leftTemp.Process();

  if(!getDictLocked())
  {
    leftO2.setTempFault(GetIntValueByTag(FLT_TP_L));
    leftO2.setO2Fault(GetIntValueByTag(FLT_CH_L));
  };

  leftO2.SetCelFT(leftTemp.getCelFT());

  leftO2.Process();
  if(!getDictLocked())
  {
    leftHN.setTempFault(GetIntValueByTag(FLT_TP_L)); 
    leftHN.setTempFault(GetIntValueByTag(FLT_CH_L));
  };                                    
  leftHN.SetEE(leftO2.GetEE());
  leftHN.Process();

  leftO2.SaveResults();
  leftTemp.SaveResults();
  leftHN.SaveResults();  

  if(!getDictLocked())
  {
    rightTemp.setTempFault(GetIntValueByTag(FLT_TP_R));
  };
  rightTemp.Process();

  if(!getDictLocked())
  {
    rightO2.setTempFault(GetIntValueByTag(FLT_TP_R));
    rightO2.setO2Fault(GetIntValueByTag(FLT_CH_R));
  };  
  rightO2.SetCelFT(rightTemp.getCelFT());

  rightO2.Process();
  if(!getDictLocked())
  {
    rightHN.setTempFault(GetIntValueByTag(FLT_TP_R));
    rightHN.setO2Fault(GetIntValueByTag(FLT_CH_R));
  };
  rightHN.SetEE(rightO2.GetEE());
  rightHN.Process();

  rightO2.SaveResults();    
  rightTemp.SaveResults();
  rightHN.SaveResults(); 

 // clrDebugPin();
};
//------------------------------------------------------------------------------
Processing*processing;

Processing*GetProcessing(void)
{return processing;};

void ProcessingHandler(void)
{
  processing->ProcessDSP();
}

void ProcessInit(void)
{
  processing = new Processing();
  processing->LoadVariables();
  SetProcessingHandler(&ProcessingHandler);
}

void LoadProcessingVariables(void)
{
  processing->LoadVariables();
}
