#include "system.h"

#define CHAR_SPACE ' '
#define CHAR_QUOTE '"'
#define CHAR_CODE_SUCCESS '0'
#define ERR_CODE1_4003     "-4003 "
#define ERR_CODE2_4002     "-4002 "

SEARIL_STRUCT    Searil __attribute__ ((aligned (4u)));


const char Cmd_Table[INDEX_CMD_MAX_COUNT][32]={

   "model",
   "ble_config",
   "mcu_version",
   "get_down",
   "result ",
   "error",
   "properties_changed ",
   "event_occured",
   "set_properties",
   "get_properties",
   "action",
   "MIIO_net_change",
   "update_fw",
   "echo",
   "mcu_boot fail", 
   "net",
   "time",
   "mac",
   "version",
   "help",
   "true",
   "false",
   "restore",
   "factory",
   "result \"ready\""   
};
const char manufacturer[]="0 \"xincheng\" ";



const char ThreeChannelInfo[][22] ={

   {" cnph.plug.yd01"},  //modle
   {"31968"},           //serial_number

};
const char FiveChannelInfo[][22] ={

   {" cnph.plug.yd05"},  //modle
   {"36922"},           //serial_number

};

enum{

   SIID_DEVICE_INFORMATION =0,
   SIID_SWITCH_1,
   SIID_SWITCH_2,
   SIID_SWITCH_3,
   SIID_SWITCH_4,
   SIID_SWITCH_5,
   SIID_CUSTOM,
   SIID_PHYSICAL_LOCK,
   MAX_COUNT

}SIID_INDEX;

const char ProtocolInfo[][14]={

    {'1','1','2','3','4'},                                     //siid piid piid piid piid 
    {'2','1','4','1'},                                         //siid piid piid piid aiid
    {'3','1','4','1'},                                         //siid piid piid piid aiid
    {'4','1','4','1'},                                         //siid piid piid piid aiid
    {'5','1','4','1'},                                         //siid piid piid piid aiid
    {'6','1','4','1'},                                         //siid piid piid piid aiid
    {'7','1','2','3','4','5','6','7','8','9','1','0','1','1'}, //siid piid piid piid piid
    {'8','1'}
};


// 指令查找表：字符串 + 长度 + 命令ID
typedef struct {
    const char *str;
    uint8_t len;
    uint8_t cmd;
} CmdItem;

// 指令定义（和你代码完全对应）
#define P_CMD_DOWN_SET_PROP    1
#define P_CMD_DOWN_NONE        2
#define P_CMD_DOWN_GET_PROP    3
#define P_CMD_DOWN_ACTION      4
#define P_CMD_DOWN_UPDATE_FW   5
#define P_CMD_DOWN_NET_CHANGE  6
#define P_CMD_DOWN_MCU_VER     7
#define P_CMD_OK               8
#define P_CMD_LOCAL            9
#define P_CMD_ERROR            10

// 查找表
const CmdItem CmdTable[] = {
    {"set_properties",      14, P_CMD_DOWN_SET_PROP},
    {"none",                 4, P_CMD_DOWN_NONE},
    {"get_properties",      14, P_CMD_DOWN_GET_PROP},
    {"action",               6, P_CMD_DOWN_ACTION},
    {"update_fw",            9, P_CMD_DOWN_UPDATE_FW},
    {"MIIO_net_change",     15, P_CMD_DOWN_NET_CHANGE},
    {"MIIO_mcu_version_req",15, P_CMD_DOWN_MCU_VER},
    {"ok",                   2, P_CMD_OK},
    {"local",                5, P_CMD_LOCAL},
    {"error",                5, P_CMD_ERROR},
};

#define CMD_COUNT (sizeof(CmdTable)/sizeof(CmdItem))
    
//****************************************************************//
//函数名称: static inline void Tx_Fill_Str(const char *str)
//函数功能: 填充单个字符串到TxBuf
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
static inline void Tx_Fill_Char(uint8_t ch) {
    
    Searil.TxBuf[Searil.length++] = ch;
}
//****************************************************************//
//函数名称: static inline void Tx_Fill_Str(const char *str)
//函数功能: 填充字符串到TxBuf
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
static inline void Tx_Fill_Str(const char *str) {
    
    strcpy(&Searil.TxBuf[Searil.length], str);
    
    Searil.length += strlen(str);
    
    Tx_Fill_Char(CHAR_SPACE);
}
//****************************************************************//
//函数名称: static inline void Tx_Fill_Str(const char *str)
//函数功能: 填充SIID + 空格
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
static inline void Tx_Fill_Siid(const char *siid) {
    
    Tx_Fill_Char(*siid);
    
    Tx_Fill_Char(CHAR_SPACE);
    
}
//****************************************************************//
//函数名称: static inline void Tx_Fill_Str(const char *str)
//函数功能: 填充PIID + 空格
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
static inline void Tx_Fill_Piid(const char *piid) {
    
    Tx_Fill_Char(*piid);
    
    Tx_Fill_Char(CHAR_SPACE);
    
}

//****************************************************************//
//函数名称: static inline void Tx_Fill_Str(const char *str)
//函数功能: 填充固定成功码(0) + 空格
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
static inline void Tx_Fill_Success(void) {
    
    Tx_Fill_Char(CHAR_CODE_SUCCESS);
    
    Tx_Fill_Char(CHAR_SPACE);
}

//****************************************************************//
//函数名称: static inline void Tx_Fill_ErrCode(const char *str)
//函数功能: 填充固定成功码(0) + 空格
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
static inline void Tx_Fill_ErrCode(void) {
    
    strcpy((char*)&Searil.TxBuf[Searil.length], ERR_CODE1_4003);
    
    Searil.length += 6;
}
//****************************************************************//
//函数名称: static inline void Tx_Fill_ErrCode2(const char *str)
//函数功能: 填充固定成功码(0) + 空格
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
static inline void Tx_Fill_ErrCode2(void) {
    
    strcpy((char*)&Searil.TxBuf[Searil.length], ERR_CODE2_4002);
    
    Searil.length += 6;
}

//****************************************************************//
//函数名称: void Protocol_Update_SendConfig(uint8_t sendcount,uint8_t sendmax,uint8_t tx_state)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Update_SendConfig(uint8_t sendcount,uint8_t sendmax,uint8_t tx_state){

    Searil.send_count=sendcount;
    
    Searil.send_max=sendmax;
    
    Searil.Tx_State= tx_state;
}

//****************************************************************//
//函数名称: void Protocol_TxBuf_Fill(char*data,uint16_t length,uint8_t send_times,uint8_t type)
//函数功能: 填充
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_TxBuf_Fill(uint16_t length,uint8_t type){

   
    Searil.length=length;
    
    Searil.TxBuf[Searil.length-1]=0x0D;
    
    Searil.send_count=0;
    
    Searil.send_max=1;
    
    Searil.wait_feedback_type=type;
    
}
//****************************************************************//
//函数名称: void Protocol_SerialTxCommProcess(void)
//函数功能: 设置模组名称
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_SerialTxCommProcess(void){
    
    if((Searil.Tx_State==Tx_Request)||(Searil.Tx_State==Tx_Repeat)){
     
       Searil.Tx_Delays=100;
        
       Searil.tx_count=0;
        
       if(Searil.Tx_State==Tx_Request)
         Searil.send_count=0;
       
       Searil.Tx_State=Tx_WaitComplete;
       
      #if defined(USED_USART_1)
       std_usart_cr1_interrupt_enable(USART1,USART_CR1_INTERRUPT_TXE);
      #else
       std_lpuart_cr1_interrupt_enable(LPUART1, LPUART_CR1_INTERRUPT_TXE);
      #endif
    }
}
//****************************************************************//
//函数名称: uint16_t Protocol_Start_Number(char *data)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
uint16_t Protocol_Start_Number(char *data){

    uint16_t start_number=strlen(data)*sizeof(char);
    
    return  start_number;
}
//****************************************************************//
//函数名称: void Protocol_Send_GetDown(void)
//函数功能: 发射get_down
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Send_GetDown(void){

    strcpy(Searil.TxBuf,Cmd_Table[INDEX_CMD_GET_DOWN]);
    
    Protocol_TxBuf_Fill(strlen(Cmd_Table[INDEX_CMD_GET_DOWN])*sizeof(char)+1,wait_feedback_get_down);
    
    Searil.Tx_State=Tx_Request;

}
//****************************************************************//
//函数名称: void Protocol_get_net_cmd(void)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Send_GetNet(void){

    strcpy(Searil.TxBuf,Cmd_Table[INDEX_CMD_NET]);
    
    Protocol_TxBuf_Fill(strlen(Cmd_Table[INDEX_CMD_NET])*sizeof(char)+1,wait_feeback_check_net);
    
    Searil.Tx_State=Tx_Request;
}
//****************************************************************//
//函数名称: void Protocol_Send_Update_Start(void)
//函数功能: 发射开始升级
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Send_Update_Ready(void){

    strcpy(Searil.TxBuf,Cmd_Table[INDEX_CMD_RESULT_READY]);
    
    Protocol_TxBuf_Fill(strlen(Cmd_Table[INDEX_CMD_RESULT_READY])*sizeof(char)+1,wait_feedback_update_start);
    
    Searil.Tx_State=Tx_Request;

}
//****************************************************************//
//函数名称: void Protocol_Send_GetTime(void)
//函数功能: 获取当前时间
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Send_GetTime(void){
    
    //清除获取当前时间标志位
    System.current_time_is_updated=0;
    
    strcpy(Searil.TxBuf,(char*)Cmd_Table[INDEX_CMD_TIME]);
    
    Protocol_TxBuf_Fill(strlen(Cmd_Table[INDEX_CMD_TIME])*sizeof(char)+1,wait_feeback_current_time);
    
    Searil.Tx_State=Tx_Request;
    
}
//****************************************************************//
//函数名称: void Protocol_Send_Boot_Fail(void)
//函数功能: 发射升级失败
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2023.6.13 
//***************************************************************//
void Protocol_Send_Boot_Fail(void){

    strcpy(Searil.TxBuf,(char*)Cmd_Table[INDEX_CMD_BOOT_FAIL]);
    
    Protocol_TxBuf_Fill(strlen(Cmd_Table[INDEX_CMD_BOOT_FAIL])*sizeof(char)+1,wait_feedback_boot_fail_ok);
    
    Searil.Tx_State=Tx_Request;
}

//****************************************************************//
//函数名称: void Protocol_Send_Restor(void)
//函数功能: 发送删除配网
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2023.6.13 
//***************************************************************//
void Protocol_Send_Restor(void){
    
    strcpy(Searil.TxBuf,(char*)Cmd_Table[INDEX_CMD_RESTORE]);
    
    Protocol_TxBuf_Fill(strlen(Cmd_Table[INDEX_CMD_RESTORE])*sizeof(char)+1,wait_feeback_restor);
    
    Searil.Tx_State=Tx_Request;
}
//****************************************************************//
//函数名称: void Protocol_Send_Factory(void)
//函数功能: 发送进入工厂模式
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2023.6.13 
//***************************************************************//
void Protocol_Send_Factory(void){

    strcpy(Searil.TxBuf,(char*)Cmd_Table[INDEX_CMD_FACTORY]);
    
    Protocol_TxBuf_Fill(strlen(Cmd_Table[INDEX_CMD_FACTORY])*sizeof(char)+1,wait_feeback_factory);
    
    Searil.Tx_State=Tx_Request;

}
//****************************************************************//
//函数名称: uint8_t Protocol_Switch_Siid_Check(char*temp)
//函数功能: 协议通道确认
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2023.6.13 
//***************************************************************//
uint8_t Protocol_Switch_Siid_Check(char* temp){

    if(strncmp(temp,ProtocolInfo[SIID_SWITCH_1],1)==0)
       return 1;
    if(strncmp(temp,ProtocolInfo[SIID_SWITCH_2],1)==0)
       return 2;
    if(strncmp(temp,ProtocolInfo[SIID_SWITCH_3],1)==0)
       return 3;
    if(strncmp(temp,ProtocolInfo[SIID_SWITCH_4],1)==0)
       return 4;
    if(strncmp(temp,ProtocolInfo[SIID_SWITCH_5],1)==0)
       return 5;
    return 0;
}
//****************************************************************//
//函数名称: uint8_t Protocol_Switch_Piid_SwitchStatus_Check(char* temp)
//函数功能: 开关状态确认
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2023.6.13 
//***************************************************************//
uint8_t Protocol_Switch_Piid_SwitchStatus_Check(char* temp){
    
    if(strncmp(temp,ProtocolInfo[SIID_SWITCH_1]+1,1)==0)
       return 1;
    if(strncmp(temp,ProtocolInfo[SIID_SWITCH_2]+1,1)==0)
       return 1;
    if(strncmp(temp,ProtocolInfo[SIID_SWITCH_3]+1,1)==0)
       return 1; 
    if(strncmp(temp,ProtocolInfo[SIID_SWITCH_4]+1,1)==0)
       return 1; 
    if(strncmp(temp,ProtocolInfo[SIID_SWITCH_5]+1,1)==0)
       return 1; 
    return 0;
}
//****************************************************************//
//函数名称: uint8_t Protocol_Switch_Piid_Mode_Check(char* temp)
//函数功能: 开关模式确认
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2023.6.13 
//***************************************************************//
uint8_t Protocol_Switch_Piid_Mode_Check(char* temp){

    if(strncmp(temp,ProtocolInfo[SIID_SWITCH_1]+2,1)==0)
       return 1;
    if(strncmp(temp,ProtocolInfo[SIID_SWITCH_2]+2,1)==0)
       return 1;
    if(strncmp(temp,ProtocolInfo[SIID_SWITCH_3]+2,1)==0)
       return 1; 
    if(strncmp(temp,ProtocolInfo[SIID_SWITCH_4]+2,1)==0)
       return 1; 
    if(strncmp(temp,ProtocolInfo[SIID_SWITCH_5]+2,1)==0)
       return 1; 
    return 0;
}
//****************************************************************//
//函数名称: uint8_t Protocol_Custom_Timer_Group_Number_Check(char* temp)
//函数功能: 定时组确认
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2023.6.13 
//***************************************************************//
uint8_t Protocol_Custom_Timer_Group_Number_Check(char* temp){

    if(strncmp(temp,ProtocolInfo[SIID_CUSTOM]+1,1)==0||strncmp(temp,ProtocolInfo[SIID_CUSTOM]+2,1)==0)
       return 1;
    if(strncmp(temp,ProtocolInfo[SIID_CUSTOM]+3,1)==0||strncmp(temp,ProtocolInfo[SIID_CUSTOM]+4,1)==0)
       return 2;
    if(strncmp(temp,ProtocolInfo[SIID_CUSTOM]+5,1)==0||strncmp(temp,ProtocolInfo[SIID_CUSTOM]+6,1)==0)
       return 3;
    if(strncmp(temp,ProtocolInfo[SIID_CUSTOM]+7,1)==0||strncmp(temp,ProtocolInfo[SIID_CUSTOM]+8,1)==0)
       return 4;
    if(strncmp(temp,ProtocolInfo[SIID_CUSTOM]+9,1)==0||strncmp(temp,ProtocolInfo[SIID_CUSTOM]+10,2)==0)
       return 5;
    return 0;
}
//****************************************************************//
//函数名称: uint8_t Protocol_Timer_GroupNumber_Piid_Check(char* temp) 
//函数功能: 定时组确认
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2023.6.13 
//***************************************************************//
uint8_t Protocol_Timer_GroupNumber_Piid_Check(char* temp) {

    if(strncmp(temp,ProtocolInfo[SIID_CUSTOM]+1,1)==0)
       return 1;
    if(strncmp(temp,ProtocolInfo[SIID_CUSTOM]+3,1)==0)
       return 2;
    if(strncmp(temp,ProtocolInfo[SIID_CUSTOM]+5,1)==0)
       return 3;
    if(strncmp(temp,ProtocolInfo[SIID_CUSTOM]+7,1)==0)
       return 4;
    if(strncmp(temp,ProtocolInfo[SIID_CUSTOM]+9,1)==0)
       return 5;
    return 0;
}
//****************************************************************//
//函数名称: uint8_t Protocol_Timer_Group_Set_Piid_Check(char* temp) 
//函数功能: 定时组 设置piid
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2023.6.13 
//***************************************************************//
uint8_t Protocol_Timer_Group_Set_Piid_Check(char* temp) {

    if(strncmp(temp,ProtocolInfo[SIID_CUSTOM]+2,1)==0)
       return 1;
    if(strncmp(temp,ProtocolInfo[SIID_CUSTOM]+4,1)==0)
       return 2;
    if(strncmp(temp,ProtocolInfo[SIID_CUSTOM]+6,1)==0)
       return 3;
    if(strncmp(temp,ProtocolInfo[SIID_CUSTOM]+8,1)==0)
       return 4;
    if(strncmp(temp,ProtocolInfo[SIID_CUSTOM]+10,2)==0)
       return 5;
    return 0;
}



//****************************************************************//
//函数名称: void Protocol_Cal_GroupNumber(void)
//函数功能: 计算数值组数目
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Down_Set_Properties_Process(uint8_t Count){
    
      char *temp=NULL;

      //pass down   
      temp=strtok(Searil.RxBuf," ");
      //pass set properties
      temp=strtok(NULL," ");

      strcpy(Searil.TxBuf,(char*)Cmd_Table[INDEX_CMD_RESULT]);
      //从第几字节开始
      Searil.length=Protocol_Start_Number((char*)Cmd_Table[INDEX_CMD_RESULT]);
      
      for(uint8_t i=0; i < Count ; i++){
         //得到Siid
         temp=strtok(NULL," ");
         //填充siid
         Tx_Fill_Siid(temp); 

         if(Protocol_Switch_Siid_Check(temp)){
             
           uint8_t channel = Protocol_Switch_Siid_Check(temp) - 1;
             
           temp = strtok(NULL, " ");
           //填充piid 
           Tx_Fill_Piid(temp);
               
           if(Protocol_Switch_Piid_SwitchStatus_Check(temp)){
                   
             temp=strtok(NULL," ");
             //长关 
             if(!strncmp(temp,"false",5)){
                      
                Protocol_Change_Mode(CLOSE_STATE,channel); 
                //填充code，修改成功 
                Tx_Fill_Success();
                 
             }else if(strncmp(temp,"true",4)==0){
                    
                Protocol_Change_Mode(OPEN_STATE,channel);
                //填充code，修改成功 
                Tx_Fill_Success();
                    
             }else
                Tx_Fill_ErrCode();
             
           }else if(Protocol_Switch_Piid_Mode_Check(temp)){

             temp=strtok(NULL," "); 
                   
             if(!strncmp(temp,"0",1))
               Protocol_Change_Mode(AUTO_STATE,channel);
             else if(!strncmp(temp,"1",1))
               Protocol_Change_Mode(OPEN_STATE,channel);
             else if(!strncmp(temp,"2",1))
               Protocol_Change_Mode(CLOSE_STATE,channel);
             else{
               Tx_Fill_ErrCode();
               continue;
             }
             //填充code，修改成功 
             Tx_Fill_Success();
           }
             //custom
         }else if(strncmp(temp,ProtocolInfo[SIID_CUSTOM],1)==0){
             
           temp=strtok(NULL," ");
             
           uint8_t Channel=Protocol_Custom_Timer_Group_Number_Check(temp);
             
           Tx_Fill_Piid(temp);
             
           if(Protocol_Timer_GroupNumber_Piid_Check(temp)){
                     
             temp=strtok(NULL," ");  
               
             uint8_t number =atoi(temp); 
               
             //0-28内有效
             if(number<28)
                Tx_Fill_Success();
             else
                Tx_Fill_ErrCode();
                   
           }else if(Protocol_Timer_Group_Set_Piid_Check(temp)){
             //将定时数据发送到数组
             temp=strtok(NULL," ");
             //是字符串
             if(strncmp(temp,"\"",1)==0){
                //code
                Tx_Fill_Success();
                 
                Protocol_TimingGroup_Set(temp,Channel); 
                  
             }else
                Tx_Fill_ErrCode(); 
             
           }
         //设备信息,因为是写入，所以反馈-4002
         }else if(!strncmp(temp,ProtocolInfo[SIID_DEVICE_INFORMATION],1)){
            
            temp = strtok(NULL, " ");
            //写入Piid
            Tx_Fill_Piid(temp);
             
            Tx_Fill_ErrCode2();
             
         }else if(!strncmp(temp,ProtocolInfo[SIID_PHYSICAL_LOCK],1)){
            
            temp = strtok(NULL, " ");
             
            Tx_Fill_Piid(temp);
               
            if(!strncmp(temp,ProtocolInfo[SIID_PHYSICAL_LOCK]+1,1)){
                
               temp=strtok(NULL," ");
                  //长关 
               if(!strncmp(temp,"false",5))
                 SystemInfo.keylocked=0;
               else if(strncmp(temp,"true",4)==0)
                 SystemInfo.keylocked=1;
               else{
                   
                 Tx_Fill_ErrCode();
                 continue;
               }
               System_Properties_Change_Cal(0,Lock_Change);
               Display.update_lcd = 1;
               Tx_Fill_Success();
            }
         }
      }
     Protocol_TxBuf_Fill(Searil.length,wait_feedback_result);
      
     Searil.Tx_State=Tx_Request; 
}

//****************************************************************//
//函数名称: void Protocol_Get_Properties_Process(uint8_t group)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Get_Properties_Process(uint8_t count){
    
      //pass down   
      char * temp = strtok(Searil.RxBuf," ");
      //pass get_properties
      temp=strtok(NULL," ");

      strcpy(Searil.TxBuf,Cmd_Table[INDEX_CMD_RESULT]);
      //从第几字节开始
      Searil.length=Protocol_Start_Number((char*)Cmd_Table[INDEX_CMD_RESULT]);

      for(uint8_t i=0;i<count;i++){
        //得到Siid
        temp=strtok(NULL," "); 
        //填充siid
        Tx_Fill_Siid(temp);
        //siid 
        if(!strncmp(temp,ProtocolInfo[SIID_DEVICE_INFORMATION],1)){
            
           //得到piid
           temp=strtok(NULL," "); 
           //填充piid
           Tx_Fill_Piid(temp); 

           if(!strncmp(temp,ProtocolInfo[SIID_DEVICE_INFORMATION]+1,1)) {

             Tx_Fill_Str(manufacturer);
               
           }else if(strncmp(temp,ProtocolInfo[SIID_DEVICE_INFORMATION]+2,1)==0){
             

             Tx_Fill_Str(SystemInfo.ChannelCount==3 ? ThreeChannelInfo[INFO_modle] : FiveChannelInfo[INFO_modle]);  
               
           }else if(strncmp(temp,ProtocolInfo[SIID_DEVICE_INFORMATION]+3,1)==0){
               
             Tx_Fill_Str(SystemInfo.ChannelCount==3 ? ThreeChannelInfo[INFO_modle] : FiveChannelInfo[INFO_modle]);  
               
           }else if(strncmp(temp,ProtocolInfo[SIID_DEVICE_INFORMATION]+4,1)==0){
               
             char number[4]={0};
             
             number[0]=VERSION/1000+'0';
             number[1]=VERSION%1000/100+'0';
             number[2]=VERSION%1000%100/10+'0';
             number[3]=VERSION%1000%100%10+'0';   
             Tx_Fill_Success();
             Tx_Fill_Char(CHAR_QUOTE);
             strcat(Searil.TxBuf, number);
             Tx_Fill_Char(CHAR_QUOTE);
             Tx_Fill_Char(CHAR_SPACE);
           }
        }else if(Protocol_Switch_Siid_Check(temp)){
            
           uint8_t channel = Protocol_Switch_Siid_Check(temp) - 1;;
            
           temp=strtok(NULL," "); 
           //填充piid
           Tx_Fill_Piid(temp);
            
           TIMING_INFO *chan = &SystemInfo.time_channel[channel]; 
            
           if(Protocol_Switch_Piid_SwitchStatus_Check(temp)) {
             //填充code，填充数值
             Tx_Fill_Success();
               
             Tx_Fill_Str(chan->Relays_States ? Cmd_Table[INDEX_CMD_TRUE] : Cmd_Table[INDEX_CMD_FALSE]);
           }
           else if(Protocol_Switch_Piid_Mode_Check(temp))  {
               
             Tx_Fill_Success();
               
             if (chan->Mode == CLOSE_STATE)      
               Tx_Fill_Char('2');
             else if (chan->Mode == OPEN_STATE)  
               Tx_Fill_Char('1');
             else if (chan->Mode == AUTO_STATE) 
               Tx_Fill_Char('0');
             
               Tx_Fill_Char(CHAR_SPACE);
             
           }else{
              Searil.length-=8;
           }
        }else if(!strncmp(temp,ProtocolInfo[SIID_PHYSICAL_LOCK],1)){
            
           temp = strtok(NULL, " ");
           // 严格按你的函数填充PIID
           Tx_Fill_Piid(temp); 
            
           if(!strncmp(temp,ProtocolInfo[SIID_PHYSICAL_LOCK]+1,1)) {
               
             Tx_Fill_Success();
               
             Tx_Fill_Str(SystemInfo.keylocked ? Cmd_Table[INDEX_CMD_TRUE] : Cmd_Table[INDEX_CMD_FALSE]);
             
           }
        } else if(strncmp(temp,ProtocolInfo[SIID_CUSTOM],1)==0){
            
           temp = strtok(NULL, " ");
           // 严格按你的函数填充PIID
           Tx_Fill_Piid(temp);
           
           uint8_t Channel=Protocol_Custom_Timer_Group_Number_Check(temp); 
            
           TIMING_INFO *t_chan = &SystemInfo.time_channel[Channel];
            
           if(Protocol_Timer_GroupNumber_Piid_Check(temp)){
               
             Tx_Fill_Success();
               
             if (System.timer_Enable_Count[Channel] >= 10) {
                 
               Tx_Fill_Char(System.timer_Enable_Count[Channel]/10 + 0x30);
                 
               Tx_Fill_Char(System.timer_Enable_Count[Channel]%10 + 0x30);
                 
             } else {
                 
               Tx_Fill_Char(System.timer_Enable_Count[Channel] + 0x30);
             }
             Tx_Fill_Char(CHAR_SPACE);
            
           }else if(Protocol_Timer_Group_Set_Piid_Check(temp)){
               
             Tx_Fill_Success();
               
             Tx_Fill_Char(CHAR_QUOTE);
               
             for(uint8_t i=0;i<28;i++){
               
               uint8_t disp_none1 = t_chan->timing[2*i].disp_none;
               uint8_t disp_none2 = t_chan->timing[2*i+1].disp_none;
               uint8_t en1  = t_chan->timing[2*i].enable;
               uint8_t h1   = t_chan->timing[2*i].hour;
               uint8_t m1   = t_chan->timing[2*i].minutes;
               uint8_t en2  = t_chan->timing[2*i+1].enable;
               uint8_t h2   = t_chan->timing[2*i+1].hour;
               uint8_t m2   = t_chan->timing[2*i+1].minutes;

               Tx_Fill_Char(System_Number_To_ASSIIC(((en1<<7u)|(disp_none1<<6u)|h1) >> 4u));
                 
               Tx_Fill_Char(System_Number_To_ASSIIC(((en1<<7u)|h1) & 0x0F));
                 
               Tx_Fill_Char(System_Number_To_ASSIIC(m1 >> 4));
                 
               Tx_Fill_Char(System_Number_To_ASSIIC(m1 & 0x0F));

               if (!en1 && !h1 && !m1 && !en2 && !h2 && !m2) {
                   
                 Tx_Fill_Char('f');
                   
                 Tx_Fill_Char('f');
                   
               } else {
                   
                 Tx_Fill_Char(System_Number_To_ASSIIC(t_chan->timing[2*i].week));
                   
                 Tx_Fill_Char(System_Number_To_ASSIIC(t_chan->timing[2*i+1].week));
                   
               }

               Tx_Fill_Char(System_Number_To_ASSIIC(((en2<<7u)|(disp_none2<<6u)|h2) >> 4u));
               
               Tx_Fill_Char(System_Number_To_ASSIIC(((en2<<7u)|h2) & 0x0F));
               
               Tx_Fill_Char(System_Number_To_ASSIIC(m2 >> 4));
               
               Tx_Fill_Char(System_Number_To_ASSIIC(m2 & 0x0F));
             }
             Tx_Fill_Char(CHAR_QUOTE);
           }else
             Searil.length -= 8;
        }
        
      }
     Protocol_TxBuf_Fill(Searil.length+1,wait_feedback_result);
      
     Searil.Tx_State=Tx_Request; 
}
//****************************************************************//
//函数名称: void Protocol_Send_MCU_Version(void)
//函数功能: 发送版本
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Send_MCU_Version(void){
    
    
      char number[5]={0};
      char send_mcu_version[(strlen(Cmd_Table[INDEX_CMD_MCU_VERSION])+strlen(number))*sizeof(char)];
      number[0]=' ';
      number[1]=VERSION/1000+'0';
      number[2]=VERSION%1000/100+'0';
      number[3]=VERSION%1000%100/10+'0';
      number[4]=VERSION%1000%100%10+'0';
      strcpy(send_mcu_version,Cmd_Table[INDEX_CMD_MCU_VERSION]);
      
      strcat(send_mcu_version,number);
      
      strcpy(Searil.TxBuf,(char*)send_mcu_version);
    
      Protocol_TxBuf_Fill(strlen(send_mcu_version)+1,wait_feeback_only_mcu_vesrion);
    
     Searil.Tx_State=Tx_Request;   
      
    
}

//****************************************************************//
//函数名称: void Protocol_Send_Cmd_Too_Long(void)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Send_Cmd_Too_Long(void){


   char Txdata[]="error \"Cmd Too Long\" -5002";

   strcpy(Searil.TxBuf,(char*)Txdata);
    
   Protocol_TxBuf_Fill(strlen(Txdata)*sizeof(char)+1,wait_feedback_error_code);
    
   Searil.Tx_State=Tx_Request;   
    
}
//****************************************************************//
//函数名称: void Protocol_Send_Cmd_MemoryError(void)
//函数功能: 发射内存错误
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Send_Cmd_MemoryError(void){

  char Txdata[]="error \"memory error\" -5001";

   strcpy(Searil.TxBuf,(char*)Txdata);
    
   Protocol_TxBuf_Fill(strlen(Txdata)*sizeof(char)+1,wait_feedback_error_code);
    
   Searil.Tx_State=Tx_Request;
}

//****************************************************************//
//函数名称: void Protocol_Send_Debug_0(void)
//函数功能: 发射debug0
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Send_Debug_0(void){


   char Txdata[]="set_log_level 0";
    
   strcpy(Searil.TxBuf,(char*)Txdata);
    
   Protocol_TxBuf_Fill(strlen(Txdata)*sizeof(char)+1,wait_feedback_error_code);
    
   Searil.Tx_State=Tx_Request;

} 
//****************************************************************//
//函数名称: void Protocol_Get_Current_Time(uint8_t *temp)
//函数功能: 获取数据
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Get_Current_Time(char *temp){

    uint8_t number=0;
    number++;
    
    if(*(temp+number)==':'){
      Current.Hours= System_Char_To_Number(*(temp));
      number++;   //是数值
    } else{
      Current.Hours= System_Char_To_Number(*temp)*10;
      Current.Hours+=System_Char_To_Number(*(temp+number));
      number+=2; //数值 
    }

    if(*(temp+number+1)==':'){

      Current.Minute=System_Char_To_Number(*(temp+number));
      number+=2;
    }else{
      Current.Minute=System_Char_To_Number(*(temp+number))*10;
      number++;
      Current.Minute+=System_Char_To_Number(*(temp+number));
      number+=2;
    }
    if(*(temp+number+1)==':'){
      Current.Sec=System_Char_To_Number(*(temp+number));
      number+=2;
    }else{
      Current.Sec=System_Char_To_Number(*(temp+number))*10;
      number++;
      Current.Sec+=System_Char_To_Number(*(temp+number));
      number+=2;
    }

}
//****************************************************************//
//函数名称: void Protocol_Get_Current_Time(uint8_t *temp)
//函数功能: 获取数据
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Action_Send(uint8_t ch){


      strcpy(Searil.TxBuf,Cmd_Table[INDEX_CMD_RESULT]);
    
      Searil.length=Protocol_Start_Number((char*)Cmd_Table[INDEX_CMD_RESULT]);
    
      Searil.TxBuf[Searil.length++]=ProtocolInfo[ch+1][0];  

      Searil.TxBuf[Searil.length++]=' ';

      Searil.TxBuf[Searil.length++]=ProtocolInfo[ch+1][4];  

      Searil.TxBuf[Searil.length++]=' '; 
      //code
      Searil.TxBuf[Searil.length++]='0'; 
    
      if(!SystemInfo.time_channel[ch].Relays_States)
        Protocol_Switch_Status(1,ch);
      else
        Protocol_Switch_Status(0,ch); 

     Protocol_TxBuf_Fill(Searil.length+1,wait_feedback_result);
    
     Searil.Tx_State=Tx_Request;
      
     System_Properties_Change_Cal(ch,Mode_Change);
}
//****************************************************************//
//函数名称: void Protocol_Receive_Process(void)
//函数功能: 协议接收处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Receive_Process(char *data,uint16_t Length){
    
        uint8_t count=0;
        char Rx_cache[Length];
    
        strncpy(Rx_cache,data,Length);
    
        char *temp=NULL;
    
        if(Length>=512){

          Protocol_Cmd_Cache(CMD_TOO_LONG);
          return ;
        }
        //得到内容
        temp=strtok(Rx_cache," ");
        
        if (temp == NULL) return;
        
        uint8_t cmd_match = 0;
        
        if(strncmp(temp,"down",4)==0){
              
           temp= strtok(NULL," ");
            
           if (temp == NULL) return; 
            
           for (uint8_t i = 0; i < CMD_COUNT; i++) {
               
             if (strncmp(temp, CmdTable[i].str, CmdTable[i].len) == 0) {
                 
               cmd_match = CmdTable[i].cmd;
                 
               break;
                 
             }
           }
           switch (cmd_match) {
           
              case P_CMD_DOWN_SET_PROP:
                 count = 0;
               
                 Searil.DataGoroupsNumber = 0;
               
                 while ((temp = strtok(NULL, " ")) != NULL) {
                  
                   count++;
                  
                   if (count % 3 == 0) 
                     Searil.DataGoroupsNumber++;
                 }
                 
                 Protocol_Cmd_Cache(CMD_SET_PROPERTIES_RPS);
                 
               break;
              case P_CMD_DOWN_NONE:
                  
                 __NOP();
              
               break;
              case P_CMD_DOWN_GET_PROP:
                  
                 count = 0;
              
                 Searil.DataGoroupsNumber = 0;
              
                 while ((temp = strtok(NULL, " ")) != NULL) {
                     
                   count++;
                     
                   if (count % 2 == 0) 
                     Searil.DataGoroupsNumber++;
                   
                 }
                 Protocol_Cmd_Cache(CMD_GET_PROPERTIES);
               break;
              case P_CMD_DOWN_ACTION:
                  
                 Protocol_Cmd_Cache(CMD_ACTION);
              
               break;
              case P_CMD_DOWN_UPDATE_FW:
                  
                 System_Disable_Send_Get_Down();
              
                 System.send_update_fail_enable = 0;
              
                 Protocol_Cmd_Clear();
              
                 System.wait_to_update_delays = 2000;
              
               break;
              case P_CMD_DOWN_NET_CHANGE:
                 temp = strtok(NULL, " ");
                 if (temp == NULL) break;

                 if (strncmp(temp, "offline", 7) == 0 ||
                     strncmp(temp, "unprov", 3) == 0 ||
                     strncmp(temp, "uap", 3) == 0 ||
                     strncmp(temp, "updating", 8) == 0){
                         
                   if (strncmp(temp, "updating", 8) != 0)
                     Display.disp_wifi = 0;
                   
                 }else if (strncmp(temp, "cloud", 5) == 0) {
                     
                   Display.disp_wifi = 1;
                   System_Disable_Send_Get_Down();
                   System.is_power_on_send_changed = 1;
                   System.Properties_Change = ALL_Change;
                   //   Protocol_Send_Debug_0();
                 }
              break;
              case P_CMD_DOWN_MCU_VER:
                 Protocol_Cmd_Cache(CMD_MCU_VER);
               break;

              default:
                 Protocol_Cmd_Cache(CMD_MEMORY_ERROR);
               break;

           }

        }else{
            
           for (uint8_t i = 0; i < CMD_COUNT; i++) {
               
             if (strncmp(temp, CmdTable[i].str, CmdTable[i].len) == 0) {
                 
               cmd_match = CmdTable[i].cmd;
                 
               break;
             }
             
           }
           switch (cmd_match) {    
              
             case P_CMD_OK:
                 
                if (System.is_not_allow_send_changed)
                  System.is_not_allow_send_changed = 0;
                
                switch (Searil.wait_feedback_type) {
                    
                  case wait_feedback_set_model:
                      
                      System.Model_Interactive_Step = Send_Ble_config;
                  
                      System.will_interactive_model = 1;
                  
                    break;
                  case wait_feedback_ble_config:
                      
                      System.Model_Interactive_Step = Send_Mcu_Version;
                  
                      System.will_interactive_model = 1;
                  
                    break;
                  case wait_feeback_send_mcu_vesrion:
                      
                      System.Model_Interactive_Step = Complete;
                  
                      Searil.connect_wifi_time_out = 0;
                  
                      System.will_interactive_model = 0;

                      if (SystemInfo.system_state == update_fail) {
                          
                        System.send_update_fail_enable = 1;
                          
                        System.update_fail_send_times = 0;
                          
                        System.update_fail_send_delays = 100;
                          
                      } else 
                        System_Enable_Send_Get_Down();
                      
                    break;
                  case wait_feedback_update_start:
                      
                      Protocol_Cmd_Clear();
                  
                      Protocol_Cmd_Cache(CMD_INTO_UPDATE);
                  
                    break;
                  case wait_feedback_error_code:
                  case wait_feeback_restor:
                      if (Searil.wait_feedback_type == wait_feeback_restor) {
                          
                        Display.disp_wifi = 0;
                          
                        if (SystemInfo.wifi_in_factory) {
                            
                            SystemInfo.wifi_in_factory = 0;
                            
                            SystemInfo.is_request_save = 1;
                            //SystemInfo_Save();  
                            
                        }
                        System.Model_Interactive_Step = Send_Model;
                      }
                    break;
                  case wait_feedback_boot_fail_ok:
                      
                      System.send_update_fail_enable = 0;
                  
                      SystemInfo.system_state = normal;
                  
                      SystemInfo.is_request_save = 1;
                      //SystemInfo_Save();  
                      System_Enable_Send_Get_Down();
                  
                    break;
                  case wait_feeback_factory:
                      
                      Factory_Cyc_Check_Net();
               
                  
                    break;
                  default:
                    break;
                }
               break;
                
             case P_CMD_LOCAL:
                 
                if (System_Mode_Read() == Factory_Mode) {
                    
                  Display.disp_wifi = 1;
                    
                  Display.update_lcd = 1;
                    
                }
                          
               break;
             case P_CMD_ERROR:
                 
                if (Searil.wait_feedback_type == wait_feedback_set_model ||
                   Searil.wait_feedback_type == wait_feedback_ble_config ||
                   Searil.wait_feedback_type == wait_feeback_send_mcu_vesrion)
                System.will_interactive_model = 1;
                
               break;

             default:
                if (Searil.wait_feedback_type == wait_feeback_current_time ||
                    Searil.wait_feedback_type == wait_feeback_cal_time){
                        
                   uint16_t year = (temp[0]-0x30)*1000 + (temp[1]-0x30)*100 + (temp[2]-0x30)*10 + (temp[3]-0x30);
                        
                   uint8_t month = (temp[5]-0x30)*10 + (temp[6]-0x30);
                        
                   uint8_t day   = (temp[8]-0x30)*10 + (temp[9]-0x30);

                   Current.Week = Zeller(year, month, day);
                        
                   temp = strtok(NULL, " ");
                        
                   Protocol_Get_Current_Time(temp);
                        
                   Display.update_lcd = 1;
                        
                   System.current_time_is_updated = 1;
                        
                   System_Enable_Send_Get_Down();
                }
               break;
                
                
           }
        }

     
}
//****************************************************************//
//函数名称: void Protocol_SerialRxCommProcess(void)
//函数功能: 接收完成
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_SerialRxCommProcess(void){

    if(Searil.Rx_Complete){
    
       Searil.Rx_Complete=0;

       if(SystemInfo.system_state==update_into)
         Update_Recive((XMODEM_STRUCT *)Searil.RxBuf);
       else
         Protocol_Receive_Process((char*)Searil.RxBuf,Searil.rx_count);

       
    }
}
//****************************************************************//
//函数名称: void Protocol_1ms_Timer(void)
//函数功能: 1ms处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_1ms_Timer(void){

    //等待应答，如果有应答了允许进入发送空闲状态
    if( Searil.Tx_State==Tx_WaitAck){
        
         Searil.Tx_Delays--;
         
         if( Searil.Tx_Delays==0){
             
             if(Searil.send_count<Searil.send_max){
                 
                 Searil.Tx_State=Tx_Repeat;
                 
             }else
               Searil.Tx_State=Tx_Idle;
         }             
    }
    if(Searil.Rx_Start){
  
       if(--Searil.Rx_Delays==0){
       
           Searil.Rx_Start=0u;
           Searil.Rx_Complete=1;
       }
    }
    if(System.wait_to_update_delays){
        
      if(--System.wait_to_update_delays==0)
        Protocol_Cmd_Cache(CMD_UPDATE_READY);  

    }

    

}
 //****************************************************************//
//函数名称: void Protocol_Cmd_Cache(uint8_t CmdCache)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Cmd_Cache(uint8_t CmdCache){
    
    if((CmdCache==System.Cmd)||(CmdCache==System.Cmd_Cache2)||(CmdCache==System.Cmd_Cache3)||(CmdCache==System.Cmd_Cache))
        return;
    //当前命令存在
    if(System.Cmd){
        //第二个缓存命令是否存在
        if(System.Cmd_Cache){
           //第三个缓存命令是否存在
           if(System.Cmd_Cache2){
              //第四个缓冲命令
              if(System.Cmd_Cache3)
                 System.Cmd_Cache3=CmdCache;
              else
                System.Cmd_Cache3=CmdCache;
           }else
             System.Cmd_Cache2=CmdCache;
        }else
          System.Cmd_Cache=CmdCache;
    }else
      System.Cmd=CmdCache;
}

//****************************************************************//
//函数名称: void Protocol_Process(void)
//函数功能: 协议处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Cmd_Refresh(void){

    if((System.Cmd_Cache||System.Cmd_Cache2||System.Cmd_Cache3)){
        
      System.Cmd=System.Cmd_Cache;
        
      System.Cmd_Cache=System.Cmd_Cache2;
        
      System.Cmd_Cache2=System.Cmd_Cache3;
        
      System.Cmd_Cache3=0;
    }

}
//****************************************************************//
//函数名称: void Protocol_Cmd_Clear(void)
//函数功能: 清除所有命令
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Cmd_Clear(void){
    
    System.Cmd_Cache2=0;
    
    System.Cmd_Cache3=0;
    
    System.Cmd_Cache=0;
    
    System.Cmd=0;
}
//****************************************************************//
//函数名称: void Protocol_Msg_Send(void)
//函数功能: 定时发射net
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Msg_Send(void){

    //优先级最高，属性改变
     Update_CAN_Process();
    
     if(Searil.Tx_State==Tx_Idle&&!Searil.Rx_Start){
         
        if(System.Cmd){ 
            
         switch(System.Cmd){
      
             case CMD_GET_DOWN:
               if(System.send_get_down_enable)
                Protocol_Send_GetDown();
               break;
             case CMD_MCU_VER:
                 Protocol_Send_MCU_Version();
               break;
             case CMD_TIME:
                 Protocol_Send_GetTime();
               break;
             case CMD_PROPERTIES_CHANGED:
                 Protocol_Send_Properties_Changed();
               break;
             case CMD_UPDATE_FAIL:
               if(System.send_update_fail_enable)
                 Protocol_Send_Boot_Fail(); 
               break;
             case CMD_GET_NET:
               Protocol_Send_GetNet();
               break;
             case CMD_RESTORE:
               Protocol_Send_Restor();
               break;
             case CMD_SET_PROPERTIES_RPS:
               Protocol_Down_Set_Properties_Process(Searil.DataGoroupsNumber);  
               break;
             case CMD_GET_PROPERTIES:
               Protocol_Get_Properties_Process(Searil.DataGoroupsNumber);
               break;
             case CMD_ACTION:
               Protocol_Action_Send(System.receive_channel);   
               break;
             case CMD_TOO_LONG:
               Protocol_Send_Cmd_Too_Long();  
               break;
             case CMD_UPDATE_READY:
               Protocol_Send_Update_Ready();
               break;
             case CMD_MEMORY_ERROR:
               Protocol_Send_Cmd_MemoryError();  
               break;
             case CMD_INTO_UPDATE:
                 SystemInfo.system_state=update_into;
  
                 Bsp_Erase_Page((UPDATE_ADDRESS-0x08000000)/512u,(0x08010000-UPDATE_ADDRESS)/512);
                 SystemInfo.is_request_save=1;
//                 SystemInfo_Save();
                 SystemInfo.update_count++;  
                 Protocol_Cmd_Clear();
                 Send_C_Check_Xmodem_Mode();
               break;
             default:
               break;
       
        }
        System.Cmd=0;
        Protocol_Cmd_Refresh();
      }
    }
 
}


//****************************************************************//
//函数名称: void Protocol_Process(void)
//函数功能: 协议处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Process(void){
   
    //低电压返回    
   if(System.is_power_down)
      return ;

    Protocol_SerialRxCommProcess();
   
    System_PowerOn_ConfigModel();
   
    Protocol_Msg_Send();
   
    Protocol_SerialTxCommProcess();
}
//****************************************************************//
//函数名称: void Protocol_Switch_Status(uint8_t On_Off)
//函数功能: 打开关闭
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Switch_Status(uint8_t On_Off,uint8_t channel){

   if(On_Off) {
       
     if(SystemInfo.time_channel[channel].Mode!=OPEN_STATE)
       SystemInfo.time_channel[channel].Mode=OPEN_STATE;
     
   }else{
       
     if(SystemInfo.time_channel[channel].Mode!=CLOSE_STATE)
       SystemInfo.time_channel[channel].Mode=CLOSE_STATE;
   }
   
   if((channel+1)==Current.channel)
      Current.Mode= SystemInfo.time_channel[channel].Mode;
   
   if( SystemInfo.time_channel[channel].Mode==CLOSE_STATE)
      Channel_Control(channel,RELAY_OFF,change_flag);
   
   else if( SystemInfo.time_channel[channel].Mode==OPEN_STATE)
      Channel_Control(channel,RELAY_ON,change_flag);

   Display.not_disp_mode=0;     //显示模式
   Display.update_lcd=1;

}

//****************************************************************//
//函数名称: void Protocol_Change_Mode(uint8_t mode,uint8_t channel)
//函数功能: 打开关闭
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Change_Mode(uint8_t mode,uint8_t channel){
    
    switch(mode){
        //auto
        case AUTO_STATE:
          if(System_Mode_Read()!=Normal_Mode)
            System_Mode_Set(Normal_Mode);  
          if(SystemInfo.time_channel[channel].Mode!=AUTO_STATE){
            SystemInfo.time_channel[channel].Mode=AUTO_STATE;
            if((channel+1)== Current.channel)
              Current.Mode= SystemInfo.time_channel[channel].Mode; 
          }
          if(SystemInfo.time_channel[channel].Mode==AUTO_STATE){
            Check_Near_CurrentTime_Arrary((TIMING_INFO*)&(SystemInfo.time_channel[channel]));  
          }else{
            Display.relay_state_flash_flag=0;
            Display.relay_state_flash_enable=0;
          } 
          
          Display.not_disp_mode=0;     //显示模式
          Display.update_lcd=1;  
          break;
          //开
        case OPEN_STATE:
           Protocol_Switch_Status(1,channel);
          break;
        //关
        case CLOSE_STATE:
           Protocol_Switch_Status(0,channel);   
          break;
        default:
          break;
    
    }
    System.Properties_Change|=(Mode_Change<<channel*5); 
}
//****************************************************************//
//函数名称: void Protocol_TimingGroup_Set(char *temp)
//函数功能: 定时组设置
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_TimingGroup_Set(char *temp,uint8_t ch){

   uint8_t cache[140]={0};
   
   temp++;  
   
   TIMING_INFO* chan = &SystemInfo.time_channel[ch];
   
   for(uint8_t j=0;j<140;j++)
     cache[j]=System_Char_To_Number(*(temp+j*2))*16+System_Char_To_Number(*(temp+j*2+1));
   
   for(uint8_t i = 0; i < 28; i++) {
    
     uint8_t base = 5 * i;               // 提取重复下标，只算1次
     uint8_t c0 = cache[base];
     uint8_t c1 = cache[base + 1];
     uint8_t c2 = cache[base + 2];
     uint8_t c3 = cache[base + 3];
     uint8_t c4 = cache[base + 4];

     // 指向两个定时项（彻底简化赋值）
     TIMING_BASE_STRUCT* t1 = &chan->timing[2 * i];
     TIMING_BASE_STRUCT* t2 = &chan->timing[2 * i + 1];

     // 原判断逻辑完全不变（删除冗余&0xFF）
     if((c0 == 0x00) && (c1 == 0x00) && (c3 == 0x00) && (c4 == 0x00) && ((c2 & 0x88) == 0x88)) {
        t1->enable    = 0;
        t1->hour      = 0;
        t1->minutes   = 0;
        t1->disp_none = 0;
        t1->close     = 1;

        t2->enable    = 0;
        t2->hour      = 0;
        t2->minutes   = 0;
        t2->disp_none = 0;
        t2->close     = 1;
     } else {
        t1->enable    = (c0 & 0x80) >> 7;
        t1->disp_none = (c0 & 0x40) >> 6;
        t1->hour      = c0 & 0x3F;
        t1->minutes   = c1;
        t1->week      = (c2 & 0xF0) >> 4;
        t1->close     = (c2 & 0x80) >> 7;

        t2->week      = c2 & 0x0F;
        t2->enable    = (c3 & 0x80) >> 7;
        t2->disp_none = (c3 & 0x40) >> 6;
        t2->hour      = c3 & 0x3F;
        t2->minutes   = c4;
        t2->close     = (c2 & 0x08) >> 4;
     }
   }

   if(System_Mode_Read()!=Normal_Mode)
     System_Mode_Set(Normal_Mode);
   
   Display.col_not_flash=0u;
   
   Display.not_disp_mode=0;     //显示模式
   
   Display.update_lcd=1;  
   //通道定时更改扫描，
   Check_Near_CurrentTime_Arrary(chan);

}
//****************************************************************//
//函数名称: void Protocol_Send_Properties_Changed(void)
//函数功能: 发射属性更改
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
uint8_t Protcol_Properties_Changed_Check(uint32_t properties ){

    uint8_t SendProperties=0;

    //右移5位看下一组
    if(properties&ALL_Change){

      if(properties&0x1F){
          
        System.Properties_Change= properties&0xFFFFFFE0;
          
        System.receive_channel=0;
          
      }else if(properties&(0x1F<<5)){
          
        System.Properties_Change= properties&0xFFFFFC00;
          
        System.receive_channel=1;  
          
      }else if(properties&(0x1F<<10)){
          
        System.Properties_Change= properties&0xFFFF8000;
          
        System.receive_channel=2;
          
      }else if(properties&(0x1F<<15)){
          
        System.Properties_Change= properties&0xFFFE0000;
          
        System.receive_channel=3;
          
      }else if(properties&(0x1F<<20)){
          
        System.Properties_Change = 0xFFF00000;
          
        System.receive_channel=4;
          
      }
      SendProperties= (properties>>( System.receive_channel*5))&0x1F;
    }
 
    return SendProperties;
}
//****************************************************************//
//函数名称: void Protocol_Send_Properties_Changed(void)
//函数功能: 发射属性更改
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Send_Properties_Changed(void){
    
    
      uint8_t ch = System.receive_channel;
    
      TIMING_INFO *chan = &SystemInfo.time_channel[ch];
    
      Searil.length=strlen(Cmd_Table[INDEX_CMD_PROPERTIES_CHANGED])*sizeof(char);
    
      strcpy(Searil.TxBuf,Cmd_Table[INDEX_CMD_PROPERTIES_CHANGED]);
    
      uint8_t Need_Report_Pro = Protcol_Properties_Changed_Check(System.Properties_Change);
       //===================== 开关状态变化 =====================
      if(Switch_Change & Need_Report_Pro){
          
         Tx_Fill_Siid(ProtocolInfo[ch + 1]);       // SIID
          
         Tx_Fill_Piid(ProtocolInfo[ch + 1] + 1);   // PIID
          
         Tx_Fill_Str(chan->Relays_States ? Cmd_Table[INDEX_CMD_TRUE] : Cmd_Table[INDEX_CMD_FALSE]);;
          
      }
      // ===================== 物理锁变化 =====================
      if(Lock_Change & Need_Report_Pro){
          
         Tx_Fill_Siid(ProtocolInfo[SIID_PHYSICAL_LOCK]);       // SIID
          
         Tx_Fill_Piid(ProtocolInfo[SIID_PHYSICAL_LOCK] + 1);   // PIID
          
         Tx_Fill_Str(SystemInfo.keylocked ? Cmd_Table[INDEX_CMD_TRUE] : Cmd_Table[INDEX_CMD_FALSE]);
          
      }
      // ===================== 模式变化 ===================== 
      if(Mode_Change & Need_Report_Pro){
          
         Tx_Fill_Siid(ProtocolInfo[ch + 1]);       // SIID
          
         Tx_Fill_Piid(ProtocolInfo[ch + 1] + 2);   // PIID
    
         if(chan->Mode == AUTO_STATE)      
           Tx_Fill_Char('0');
         else if(chan->Mode == OPEN_STATE) 
           Tx_Fill_Char('1');
         else if(chan->Mode == CLOSE_STATE)
           Tx_Fill_Char('2');
         
         Tx_Fill_Char(CHAR_SPACE);
      }
      // ===================== 定时组数量变化 =====================
      if(Group_Change & Need_Report_Pro){
          
         Tx_Fill_Siid(ProtocolInfo[SIID_CUSTOM]);               // SIID
          
         Tx_Fill_Piid(ProtocolInfo[SIID_CUSTOM] + 2*ch + 1);   // PIID
    
         if(System.timer_Enable_Count[ch] >= 10){
             
           Tx_Fill_Char(System.timer_Enable_Count[ch] / 10 + 0x30);
             
           Tx_Fill_Char(System.timer_Enable_Count[ch] % 10 + 0x30);
             
         }else{
             
           Tx_Fill_Char(System.timer_Enable_Count[ch] + 0x30);
             
         }
         Tx_Fill_Char(CHAR_SPACE);
      }
      // ===================== 定时组时间变化 =====================
      if(Group_Time_Change & Need_Report_Pro){
          
         Tx_Fill_Siid(ProtocolInfo[SIID_CUSTOM]);               // SIID
          
         uint8_t piid_idx = 2*ch + 2;
          
         Tx_Fill_Piid(ProtocolInfo[SIID_CUSTOM] + piid_idx);   // PIID
    
         // 保留你原特殊逻辑：索引==10 补填 [11]
         if(piid_idx == 10)
           Tx_Fill_Char(ProtocolInfo[SIID_CUSTOM][11]);
         
         Tx_Fill_Char(CHAR_SPACE);

         // 定时数据拼接（完全保留原逻辑 + 指针精简）
         Tx_Fill_Char(CHAR_QUOTE);
         
         for(uint8_t i=0; i<28; i++){
             
           TIMING_BASE_STRUCT *t1 = &chan->timing[2*i];
             
           TIMING_BASE_STRUCT *t2 = &chan->timing[2*i+1];
        
           uint8_t d1 = t1->disp_none;
             
           uint8_t d2 = t2->disp_none;
        
           Tx_Fill_Char(System_Number_To_ASSIIC( ((t1->enable<<7)|(d1<<6)|t1->hour) >>4 ));
             
           Tx_Fill_Char(System_Number_To_ASSIIC( ((t1->enable<<7)|t1->hour) & 0x0F ));
             
           Tx_Fill_Char(System_Number_To_ASSIIC( t1->minutes >>4 ));
             
           Tx_Fill_Char(System_Number_To_ASSIIC( t1->minutes & 0x0F ));
             
        
           if( t1->enable==0 && t1->hour==0 && t1->minutes==0 && t1->close &&
            t2->enable==0 && t2->hour==0 && t2->minutes==0 && t2->close )
           {
             Tx_Fill_Char('f');
               
             Tx_Fill_Char('f');
               
           }else{
               
             Tx_Fill_Char(System_Number_To_ASSIIC(t1->week));
               
             Tx_Fill_Char(System_Number_To_ASSIIC(t2->week));
               
           }
        
           Tx_Fill_Char(System_Number_To_ASSIIC( ((t2->enable<<7)|(d2<<6)|t2->hour) >>4 ));
           
           Tx_Fill_Char(System_Number_To_ASSIIC( ((t2->enable<<7)|t2->hour) & 0x0F ));
           
           Tx_Fill_Char(System_Number_To_ASSIIC( t2->minutes >>4 ));
           
           Tx_Fill_Char(System_Number_To_ASSIIC( t2->minutes & 0x0F ));
           
         }
         
         Tx_Fill_Char(CHAR_QUOTE);
         
         Tx_Fill_Char(CHAR_SPACE);
      }else
          Searil.length--;

      Protocol_TxBuf_Fill(Searil.length+1,wait_feedback_properties_changed);
      
      Searil.Tx_State=Tx_Request;

     if(System.is_power_on_send_changed&&!System.Properties_Change){
         
         System.is_power_on_send_changed=0;
         
         Protocol_Cmd_Cache(CMD_TIME);
         
     }
}
//****************************************************************//
//函数名称: void Protocol_Properties_Changed_Fill(void)
//函数功能: 属性更改上报
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Properties_Changed_Scan(void){

      if(!Display.disp_wifi){
          
        System.Properties_Change=0;
        return;
      }
      
      if(!System.Properties_Change)
        return;
      
      if(System.is_not_allow_send_changed)
        return;
      
      System.Properties_Change_Scan_Delays++;
      
      if(System.Properties_Change_Scan_Delays>=5){
          
         System.Properties_Change_Scan_Delays=0;
          
         Protocol_Cmd_Cache(CMD_PROPERTIES_CHANGED);
          
         System.is_not_allow_send_changed=1; 
      }
}

//****************************************************************//
//函数名称: void Protocol_Repet_Get_CurrentTime(void)
//函数功能: 重复获取当前时间
//参    数:
//返 回 值:
//说    明: 0.5S处理
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Repet_Get_CurrentTime(void){
    
      //当前时间未更新
      if(!System.current_time_is_updated && Display.disp_wifi==1)
        Protocol_Cmd_Cache(CMD_TIME);

}

