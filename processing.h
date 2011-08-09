//------------------------------------------------------------------------------
// Модуль реализует обработку результатов измерений
//------------------------------------------------------------------------------
#ifndef PROCESSING_h
#define PROCESSING_h

typedef
struct T_CLAPP{
  float x[6], y[6];
} T_CLAPP;

#define LEFT_CH  0
#define RIGHT_CH 1

class ChannelProcessor{  //abstract base class for all channel processing classes
protected: 
  char side; //left or right
  int base_temp, base_o2, base_hn;
  char general_fault;
  char temp_fault;
  virtual void Init() = 0;
  virtual void LoadVariables() = 0;
  virtual void RefreshVariables() = 0;
  virtual void Process() = 0;
  virtual void SaveResults() = 0;
public:
  void SetSide(char _side)
  {
    side = _side;
    if(side == LEFT_CH)
    {
      base_temp = BASE_T_L;
      base_o2 = BASE_O2_L;
      base_hn = BASE_HN_L;
    }
    else
    {
      base_temp = BASE_T_R;
      base_o2 = BASE_O2_R;
      base_hn = BASE_HN_R;
    };
  };
  char GetSide(void) {return side;};
  void SetGeneralFault(char value) {general_fault = value;}
  void SetTempFault(char value) {temp_fault = value;}  
};

class ChannelTemp: public ChannelProcessor{
private:
  int code_t, shift_t, cd_sh_t;
  float k_cd_t, t_t, t_cl_e, cel_t, k_f_t, t_f_t, cel_f_t, cel_f_t_1, adj_s_t,
    mism_t, mism_t_1, k_p_t, mi_p_t, mi_d_t, mi_d_t_, mi_d_t_1, mi_kd_t, k_d_t,
    k_df_t_1, k_df_t_2, t_df_t,
    ki_t, disp_t, sm_t, sk_int_t, l_comp_t, mi_dc_t, k_clc_t, clc_sh_t;
  int lim_lo_t, lim_hi_t, clc_li_t;
  //----------------------------------------------------------------------------
public:
  virtual void Init();
  virtual void LoadVariables();
  virtual void RefreshVariables();
  virtual void Process();
  virtual void SaveResults();
  
  float GetCelFT() {return cel_f_t;};
};

class ChannelO2: public ChannelProcessor{ 
private:
  int code_e, shift_e, cd_sh_e;
  float k_cd_e, e_e, k_f_e, t_f_e, e_f_e, e_f_e_1, e_lf_e, cel_f_t, cel_ff_t,
    cel_ff_t_1, k_ff_t, t_ff_t, kel_ff_t, den_o, ex_o, c_o, k_f_o, t_f_o, c_f_o,
    c_f_o_1;
  T_CLAPP clapp_o2;
  float c_kl_o, k_i_o;
  int c_o_o, sh_4_o, ci_o_o;
public:
  virtual void Init();
  virtual void LoadVariables();
  virtual void RefreshVariables();
  virtual void Process();
  virtual void SaveResults();
  
  void SetCelFT(float _cel_f_t) {cel_f_t = _cel_f_t;};
  float GetEE() {return e_e;};
};

class ChannelHN: public ChannelProcessor{ 
private:
  float e_e, k_f_h, k_ff_h, t_f_h, t_ff_h, k_d_h, t_d_h, e_f_h, e_f_h_1, e_ff_h,
    e_ff_h_1, e_ffd_h, e_ffd_h_1, e_ffd_h_, k_r_h, k_l_h, d_ffd_h, lim_h,
    klim_h, e_li_h, c_h, k_fd_h, t_fd_h, c_fd_h, c_fd_h_1;
  T_CLAPP clapp_hn;
  float c_kl_h, k_i_h;
  int ci_h, sh_4_h, ci_o_h;
public:
  virtual void Init();
  virtual void LoadVariables();
  virtual void RefreshVariables();
  virtual void Process();
  virtual void SaveResults();
  
  void SetEE(float _e_e) {e_e = _e_e;};
};

class Processing{
private:
  ChannelTemp leftTemp, rightTemp;
  ChannelO2 leftO2, rightO2;
  ChannelHN leftHN, rightHN;
public:
  Processing();
  void LoadVariables(void);
  void ProcessDSP(void);
  void Process(void);
};

void ProcessInit(void);

Processing*GetProcessing(void);

void LoadProcessingVariables(void);

#endif
