/*
  xdrv_50_tasplus.ino - Irrigation station support for Tasmota

  Added by Rob Clark
  New code to support Tasmota+
*/

#define XDRV_50             50

#define WEB_HELP		        "he"
const char S_HELP[] PROGMEM = D_HELP;

/***********************************************************************/
void HandleHelp(void){
  if (!HttpCheckPriviledgedAccess()) { return; }
    
  AddLog_P(LOG_LEVEL_DEBUG, D_LOG_HTTP, S_HELP);
  WSContentStart_P(S_HELP);
  WSContentSendStyle();
  htmlPageHeader(S_HELP);
  
  WSContentSend_P(PSTR(
  //  "<p>For more information visit the <a href='https://ubwh.github.io/' target='_blank'>" FRIENDLY_NAME "</a> website</p>"
    "<p>Read the <a href='https://github.com/UBWH/ubwh.github.io/blob/master/assets/UserGuides/' target='_blank'>User Guide</a>.</p>"
    ));
  
  WSContentSpaceButton(BUTTON_MAIN);
  
  WSContentStop();
}//HandleHelp


#ifndef FIRMWARE_MINIMAL

#define DIV_ENABLE        "en"

//#ifndef SM_URF
#ifdef MAX_WATCHDOGS
/*
const char WATCHDOG_SCRIPT_CLICK_ENABLE[] PROGMEM = 
"function cen(i){"                                          
    "eb('" DIV_ENABLE "').style.display = eb('" DIV_ENABLE "'+i).checked?'block':'none';"
"}";
*/
/********************************************************************************/
#define WEB_WATCHDOG		          "wd"
#define ID_BUTTON_TABLE		        "bt"

const char S_WATCHDOG[]  PROGMEM = D_WATCHDOG;
const char WATCHDOG_SCRIPT_CLICK_ENABLE[] PROGMEM = 
"function cen(i){"                                          
    "eb('" DIV_ENABLE "').style.display = eb('" DIV_ENABLE "'+i).checked?'block':'none';"
"}";

/***********************************************************************/
/*
const char HTTP_WATCHDOG_SCRIPT[] PROGMEM =
  "<script>"
  "var pt=[],ct=99;"
  "function ce(i,q){"                                             // Create select option
    "var o=document.createElement('option');"
    "o.textContent=i;"
    "q.appendChild(o);"
  "}"
  "function cd(){"
    "eb('ea').style.display = eb('e0').checked?'block':'none';"
  "}"
  "window.onload = function(){cd()};"
  "</script>"
  ;
*/
//#define ID_CYCLE_SECONDS  "cs"
#define ID_WATCHDOG       "wd"
#define SELECT_SOCKET     "k"//"sk"
#define SELECT_PINGS      "p"//"ps"//"sp"
#define SELECT_INTERVAL   "i"//"si"
#define INPUT_ADDRESS     "a"//"ia"
#define SELECT_CYCLE_SEC  "s"//"sc"

const char SELECTED[] PROGMEM = "selected";
const char WEB_INDEX[] PROGMEM ="%s%d";


const char WATCHDOG_SCRIPT_ON_TAB[] PROGMEM =
 "function ot(t,e){"                                   
	"var i,o;"
	"var d=%d;"
	"o=document.getElementsByClassName('button active');"
	"if(o.length){"
		"for(i=0;i<o.length;i++){"
			"o[i].classList.add('inactive');"
			"o[i].classList.remove('active');"
		"}"
	"}"
	"e.classList.add('active');"
	"for(i=1;i<=d;i++){"
	  "eb('" DIV_ENABLE "'+i).style.display=((i-1)==t)?'inline-block':'none';"
	  "eb('" ID_WATCHDOG "'+i).style.display=((i-1)==t)?'block':'none';"
	  "eb('l'+i).style.display=((i-1)==t)?'block':'none';"
	"}"	
   "cen(t+1);"
  "}"
;

//var n=[\"%s\",\"%s\",\"%s\",\"%s\"];\n

const char WATCHDOG_SCRIPT_INIT_TABS[] PROGMEM =
 "function it(){"
	"var b,i,s;"
	"s='<table width=\"100%%\">';"
	"var d=%d;"
	
	"var w=Math.floor(100/d);"
	"for(i=0;i<d;i++){"
		"b='';"
		"if(0==i){b=\" id='dP'\";}"
		"var c='inactive';"
		"if(0==i){c='active';}"
		"s+=\"<td width='\"+w+\"%%'>\";"
		"s+=\"<button type='button' class='button \"+c+\"' onclick='ot(\"+i+\",this)'\"+b+\">\";"
		"s+=\"<span id='s\"+(i+1)+\"'>\";"
    "s+='Watchdog ';" 
    "s+=i+1;"
    "//s+=n[i];\n"
		"s+=\"</span></button>\";"
	"}"
	"s+='</table>';"
	"eb('bt').innerHTML=s;"		
	"eb('dP').click();"
  "}"
  "wl(it);"
;

void HandleWatchdog(void){
  if (!HttpCheckPriviledgedAccess()) { return; }
    
  AddLog_P(LOG_LEVEL_DEBUG, D_LOG_HTTP, S_WATCHDOG);

  if (Webserver->hasArg("save")) {
    WatchdogSaveSettings();
    HandleConfiguration();
    webRedirect(PSTR("/cn"));								//PRG to Config
    return;
  }

  uint j;
  //char tmp20[20];

  WSContentStart_P(S_WATCHDOG); // <script>
                                //  Adds functions 
                                //

  WSContentSend_P(WATCHDOG_SCRIPT_CLICK_ENABLE);
  WSContentSend_P(WATCHDOG_SCRIPT_ON_TAB,MAX_WATCHDOGS);
  WSContentSend_P(WATCHDOG_SCRIPT_INIT_TABS,
 
 /*
 "function it(){"
	"var b,i,s;"
	"s='<table width=\"100%%\">';"
	"var d=%d;"
	"var n=[\"%s\",\"%s\",\"%s\",\"%s\"];"
	"var w=Math.floor(100/d);"
	"for(i=0;i<d;i++){"
		"b='';"
		"if(0==i){b=\" id='dP'\";}"
		"var c='inactive';"
		"if(0==i){c='active';}"
		"s+=\"<td width='\"+w+\"%%'>\";"  
		"s+=\"<button type='button' class='button \"+c+\"' onclick='ot(\"+i+\",this)'\"+b+\">\";"
		"s+=\"<span id='s\"+(i+1)+\"'>\";"
        "s+=n[i];"
		"s+=\"</span></button>\";"
	"}"
	"s+='</table>';"
	"eb('bt').innerHTML=s;"		
	"eb('dP').click();"
  "}"
  "wl(it);"
   ),
 */
     MAX_WATCHDOGS
 //    ,
 //    PSTR("Watchdog 1"),
//	   PSTR("Watchdog 2"),
//     PSTR("Watchdog 3"),
//     PSTR("Watchdog 4")
    );
	
 /*
 WSContentSend_P(PSTR(											   //Socket changed
 "function ck(r){"
  "var e=eb('v'+r);"
  "if(eb('p'+r).selectedIndex>1){eb('ut'+r).style.display='block';eb('ud'+r).style.display='none';}"
  "else{eb('ut'+r).style.display='none';eb('ud'+r).style.display='block';}"
  "if(eb('ud'+r).style.display=='block' && eb('ud'+r).innerHTML=='inch'){e.step='0.01';e.max='1.27';e.min='-1.27';}"
  "else{e.step='1';e.max='127';e.min='-127';}"
 "}"
 ));
*/
  //WSContentSendStyle();         //  Adds jd()
                                // </script>
                                // <style>

  
  //WSContentSendStyle_P  adds function jd() and closes  </script>	
                        //adds <style></style> 
                        // opens <body>								   
  WSContentSendStyle_P(PSTR(			
	".tl{float:left;border-radius:0;border:1px solid #%06x;padding:1px;width:6.25%%;}"
    ".inactive{background:#10537c;}.active{background:#1fa3ec;}"	
	"pre{font-size:1.4em;display:inline;}"
    "fieldset{min-width:172px;margin:auto;text-align:left;border:1;}"
	"td{text-align:center;}"
  " "                           //CrashFix
  ), WebColor(COL_FORM));  
		

  htmlTag(TM_START,TAG_FIELDSET,nullptr,PSTR("text-align:center;"));	
   htmlTag(TM_STARTEND,TAG_LEGEND,nullptr,PSTR("text-align:left;"),PSTR("<b>&nbsp;Watchdogs&nbsp;</b>")); 
    //WSContentSend_P(PSTR("<form method='post' action=''>"));
WSContentSend_P(PSTR("<form method='get' action=''>"));

      htmlTag(TM_STARTEND,TAG_DIV,PSTR(ID_BUTTON_TABLE));	
  	
      htmlTag(TM_START   ,TAG_FIELDSET);		
        htmlTag(TM_STARTEND,TAG_LEGEND,nullptr,nullptr,PSTR("&nbsp;Enable this Watchdog&nbsp;"));
        for(j=1;j<=MAX_WATCHDOGS;j++){
          WSContentSend_P(PSTR("<label id='l%d' title='Click to Enable/Disable Watchdog'>" ),j);  
            WSContentSend_P(PSTR("<input onclick='cen(%d)' id='" DIV_ENABLE "%d' type='checkbox' %s><b>Enable this Watchdog?</b>"
	  	          ),j,j,(Settings.Watchdog[j-1].enabled?"checked":""));  
    	    htmlTag(TM_END ,TAG_LABEL);
        }
      htmlTag(TM_END,TAG_FIELDSET);
  
        htmlTag(TM_START,TAG_DIV,PSTR(DIV_ENABLE));
  	      
          htmlTag(TM_START,TAG_BR);

          htmlTag(TM_START,TAG_FIELDSET);  
            htmlTag(TM_STARTEND,TAG_LEGEND,nullptr,nullptr,PSTR("&nbsp;Watchdog&nbsp;"));  	 							  
            for(j=1;j<=MAX_WATCHDOGS;j++){
              WSContentSend_P(PSTR("<div id='" ID_WATCHDOG "%d'>"),j);
		          htmlTag(TM_START,TAG_TABLE,nullptr,PSTR("width:100%%;border: 1px solid black;"));
		            htmlTag(TM_START,TAG_TR);
		              htmlTag(TM_START,TAG_TD,nullptr,PSTR("text-align:right;")); 
                    WSContentSend_P(PSTR("If&nbsp;"));
		              htmlTag(TM_START,TAG_TD); 
                    WSContentSend_P(PSTR("<select id='" SELECT_SOCKET "%u'>"),j);
                    //  for(uint i=0;i<4;i++){
                    for(uint i=0;i<TasmotaGlobal.devices_present;i++){
                      WSContentSend_P(PSTR("<option value='%u' %s>"
#ifdef SS_4CHPRO
                      "Switch"
#elif defined(SS_SHELLY1)
                      "Relay"
#else
                      "Socket"
#endif
                      " %u</option>"),i,Settings.Watchdog[j-1].socket==i?SELECTED:"",i+1);
                    }
		                htmlTag(TM_END,TAG_SELECT);
		              htmlTag(TM_START,TAG_TD,nullptr,PSTR("text-align:left;")); 
		                WSContentSend_P(PSTR("&nbsp;is ON"));
                    
		            htmlTag(TM_START,TAG_TR);
		              htmlTag(TM_START,TAG_TD,nullptr,PSTR("text-align:right;")); 
                    WSContentSend_P(PSTR("and&nbsp;"));
		              htmlTag(TM_START,TAG_TD);  
                    WSContentSend_P(PSTR("<select id='" SELECT_PINGS "%u'>"),j);
                    for(uint i=2;i<=17;i++){
                      WSContentSend_P(PSTR("<option value='%u' %s>%u</option>"),i,Settings.Watchdog[j-1].num_pings+2==i?SELECTED:"",i);
                    }
		                htmlTag(TM_END,TAG_SELECT);
		              htmlTag(TM_START,TAG_TD,nullptr,PSTR("text-align:left;")); 
		                WSContentSend_P(PSTR("&nbsp;pings"));

		            htmlTag(TM_START,TAG_TR);
		              htmlTag(TM_START,TAG_TD,nullptr,PSTR("text-align:right;")); 
                    WSContentSend_P(PSTR("at&nbsp;"));
		              htmlTag(TM_START,TAG_TD);  
                    WSContentSend_P(PSTR("<select id='" SELECT_INTERVAL "%u'>"),j);
                    for(int i=0;i<8;i++){
                      WSContentSend_P(PSTR("<option value='%u' %s>%u</option>"),i,Settings.Watchdog[j-1].interval_index==i?SELECTED:"",1<<(9-i));
                    }
		                htmlTag(TM_END,TAG_SELECT);

		              htmlTag(TM_START,TAG_TD,nullptr,PSTR("text-align:left;")); 
		                WSContentSend_P(PSTR("&nbsp;second intervals"));

		            htmlTag(TM_START,TAG_TR);
		              htmlTag(TM_START,TAG_TD,nullptr,PSTR("text-align:right;")); 
                    WSContentSend_P(PSTR("to IP V4 address&nbsp;"));
		              htmlTag(TM_START,TAG_TD);  
                    IPAddress pingIP = Settings.ping_address[j-1];
		                WSContentSend_P(PSTR(
                      "<input type='text' id='" INPUT_ADDRESS "%u' pattern='\\(IP unset\\)|((^|\\.)((25[0-5])|(2[0-4]\\d)|(1\\d\\d)|([1-9]?\\d))){4}$' placeholder='xxx.xxx.xxx.xxx' value='%s'>")
                      ,j,pingIP.toString().c_str());

		              htmlTag(TM_START,TAG_TD,nullptr,PSTR("text-align:left;")); 
		                WSContentSend_P(PSTR("&nbsp;FAIL, then"));

  	            htmlTag(TM_START,TAG_TR);
		              htmlTag(TM_START,TAG_TD,nullptr,PSTR("text-align:right;")); 
                    WSContentSend_P(PSTR("cycle socket power for&nbsp;"));
		              htmlTag(TM_START,TAG_TD); 
                    WSContentSend_P(PSTR("<select id='" SELECT_CYCLE_SEC "%u'>"),j);
                    for(uint i=1;i<=16;i++){
                      WSContentSend_P(PSTR("<option value='%u' %s>%u</option>"),i,(Settings.Watchdog[j-1].cycle_secs)+1==i?SELECTED:"",i);
                    }
		                htmlTag(TM_END,TAG_SELECT);
		              htmlTag(TM_START,TAG_TD,nullptr,PSTR("text-align:left;")); 
		                WSContentSend_P(PSTR("&nbsp;seconds."));
	
              htmlTag(TM_END,TAG_TABLE);	
              htmlTag(TM_END,TAG_DIV);	
            }//for 
      htmlTag(TM_END,TAG_FIELDSET);
     htmlTag(TM_END,TAG_DIV);//DIV_ENABLE
    WSContentSend_P(HTTP_FORM_END);		//</form></fieldset>

  WSContentSpaceButton(BUTTON_CONFIGURATION);
  
  WSContentStop();
}//HandleWatchdog
/***********************************************************************/
void WatchdogSaveSettings(void){
 char webindex[20];

 for(uint8_t i=0;i<MAX_WATCHDOGS;i++){
   snprintf_P(webindex, sizeof(webindex), WEB_INDEX,DIV_ENABLE, i+1);
   WatchdogSaveEnable(i, webindex);
   snprintf_P(webindex, sizeof(webindex), WEB_INDEX,SELECT_SOCKET, i+1);
   WatchdogSaveSocket(i, webindex);

   snprintf_P(webindex, sizeof(webindex), WEB_INDEX,SELECT_INTERVAL, i+1);
   WatchdogSaveSelectInterval(i, webindex);

   snprintf_P(webindex, sizeof(webindex), WEB_INDEX,INPUT_ADDRESS, i+1);
   WatchdogSavePingAddress(i, webindex);


   snprintf_P(webindex, sizeof(webindex), WEB_INDEX,SELECT_CYCLE_SEC, i+1);
   WatchdogSaveCycleSec(i, webindex);

   snprintf_P(webindex, sizeof(webindex), WEB_INDEX,SELECT_PINGS, i+1);
   WatchdogSavePings(i, webindex);
 }
}//WatchdogSaveSettings

void WatchdogSaveEnable(uint8_t i, char *webindex){
  Settings.Watchdog[i].enabled=Webserver->hasArg(webindex);
}

void WatchdogSaveSocket(uint8_t i, char *webindex){
  char tmp[20];
  WebGetArg(webindex, tmp, sizeof(tmp)); 
  Settings.Watchdog[i].socket=atoi(tmp); 
}

void WatchdogSavePings(uint8_t i, char *webindex){
  char tmp[20];
  WebGetArg(webindex, tmp, sizeof(tmp));   
  Settings.Watchdog[i].num_pings=atoi(tmp)-2;
}

void WatchdogSaveSelectInterval(uint8_t i, char *webindex){
  char tmp[20];
  WebGetArg(webindex, tmp, sizeof(tmp)); 
  Settings.Watchdog[i].interval_index=atoi(tmp);
}

void WatchdogSavePingAddress(uint8_t i, char *webindex){
  char tmp[40];
  WebGetArg(webindex, tmp, sizeof(tmp)); 
  ParseIp(&Settings.ping_address[i], tmp);
}

void WatchdogSaveCycleSec(uint8_t i, char *webindex){
  char tmp[20];
  WebGetArg(webindex, tmp, sizeof(tmp)); 
//  AddLog_P2(LOG_LEVEL_INFO,   PSTR("WatchdogSaveCycleSec_(%u,%s)=%s"),i,webindex,tmp);	
//return;

  Settings.Watchdog[i].cycle_secs=atoi(tmp)-1;
return;
  //AddLog_P2(LOG_LEVEL_INFO, PSTR("CSAVE WD: webIndex=%s index=%u"),webindex,i);	//OK
  //AddLog_P2(LOG_LEVEL_INFO, PSTR("CSAVE WD: webIndex=%s"),webindex);	//bad
  //AddLog_P2(LOG_LEVEL_INFO, PSTR("WDG: Settings saved"));	//bad
  //AddLog_P2(LOG_LEVEL_INFO, PSTR("WDG: webIndex=%s index=%u"),webindex,i);	//bad
  //AddLog_P2(LOG_LEVEL_INFO, PSTR("WDG12345: webIndex=%s index=%u"),webindex,i);	//OK -30ch
  //AddLog_P2(LOG_LEVEL_INFO, PSTR("WDG1234: webIndex=%s index=%u"),webindex,i);	//bad -29ch 
  //AddLog_P2(LOG_LEVEL_INFO, PSTR("WDG1234: x=%s index=%u"),webindex,i);	// OK -22 ch
  //AddLog_P2(LOG_LEVEL_INFO, PSTR("WDG: Saved123456787801"));	// OK -22 ch
  //AddLog_P2(LOG_LEVEL_INFO, PSTR("WDG: Saved1234"));	// OK -14 ch

  //Do not edit below ... no idea why but without this '14 char' output=>crashes
  //if(MAX_WATCHDOGS==i+1)
  //  AddLog_P2(LOG_LEVEL_INFO,   PSTR("WDG: Save Conf"));	// OK -14 ch
}

struct statusWatchdog_t {
  uint8_t uCounter        =0;     //Until next Ping
  uint8_t uMissedPings    =0;     //Missed Pings
  int8_t  iCycleCountdown =0;     //non-zero means in actively power cycling.
} statusWatchdog[MAX_WATCHDOGS];

/************************************************************/
void WatchdogPingResponse(uint8_t iWatchdog, uint8_t success){
  
  if(TasmotaGlobal.global_state.wifi_down ||  UpTime() < 30) return;

  if(success){
    statusWatchdog[iWatchdog].uMissedPings=0;
  } else {
    statusWatchdog[iWatchdog].uMissedPings++;
    if(statusWatchdog[iWatchdog].uMissedPings >= Settings.Watchdog[iWatchdog].num_pings+2){
      statusWatchdog[iWatchdog].uMissedPings=0;
      statusWatchdog[iWatchdog].iCycleCountdown = Settings.Watchdog[iWatchdog].cycle_secs+1;
      ExecuteCommandPower(Settings.Watchdog[iWatchdog].socket+1, POWER_OFF, SRC_IGNORE);
    }
  }
} 
/************************************************************/
void WatchdogEvery1Sec(void){
   for(uint i=0;i<MAX_WATCHDOGS;i++){
      if(!statusWatchdog[i].iCycleCountdown) continue;  
      
      statusWatchdog[i].iCycleCountdown--;
      if(!statusWatchdog[i].iCycleCountdown){
         ExecuteCommandPower(Settings.Watchdog[i].socket+1, POWER_ON, SRC_IGNORE);
         statusWatchdog[i].uMissedPings = 0;
         statusWatchdog[i].uCounter     = 1<<(9-Settings.Watchdog[i].interval_index) ;   
      }
   }
}//WatchdogEvery1Sec()  
/************************************************************/
// Minimum PingInterval is 4 secs 
void WatchdogEvery4Sec(void){  
 /*
  AddLog_P2(LOG_LEVEL_INFO, PSTR("WatchdogEvery4Sec:counters: %u %u %u %u"),
  //  ,wdCounter[0],wdCounter[1],wdCounter[2],wdCounter[3]);
   statusWatchdog[0].uCounter, statusWatchdog[1].uCounter,statusWatchdog[2].uCounter, statusWatchdog[3].uCounter);
  AddLog_P2(LOG_LEVEL_INFO, PSTR("WatchdogEvery4Sec: missed pings: %u %u %u %u"),
     statusWatchdog[0].uMissedPings, statusWatchdog[1].uMissedPings,statusWatchdog[2].uMissedPings, statusWatchdog[3].uMissedPings);
    //,wdMissedPings[0],wdMissedPings[1],wdMissedPings[2],wdMissedPings[3]
  AddLog_P2(LOG_LEVEL_INFO, PSTR("WatchdogEvery4Sec: iCycleCountdown: %u %u %u %u"),
     statusWatchdog[0].iCycleCountdown, statusWatchdog[1].iCycleCountdown,
     statusWatchdog[2].iCycleCountdown, statusWatchdog[3].iCycleCountdown);
 */

  for(uint i=0;i<MAX_WATCHDOGS;i++){
    if(!Settings.Watchdog[i].enabled                    ||
       !Settings.ping_address[i]                        ||
       (0== 1<<(9-Settings.Watchdog[i].interval_index)) ||
       (!bitRead(TasmotaGlobal.power, Settings.Watchdog[i].socket) && !statusWatchdog[i].iCycleCountdown)  
       ) continue;  

    if(0==statusWatchdog[i].uCounter){
      //Send ping
      statusWatchdog[i].uCounter=1<<(9-Settings.Watchdog[i].interval_index) ;
      int32_t res = WatchdogPing(i+1, Settings.ping_address[i]);
 
  /*
      String result;
      switch(res){
        case -2:
          result=F("Invalid IP address");         
          break;
        case -1:
          result=F("Ping already sent");         
          break;
        default:
          result=F("Sent");         
          break;
      }
      IPAddress PingIP = Settings.ping_address[i];
      AddLog_P2(LOG_LEVEL_INFO, PSTR("WDG: Ping = {\"Watchdog\":%u,\"IP\":\"%s\",\"Res\":\"%s\"}")
            ,i+1, PingIP.toString().c_str(), result.c_str());
 */
   } else {
      statusWatchdog[i].uCounter-=4;
    }
  }	
}//WatchdogEvery4Sec())
#endif //MAX_WATCHDOGS
#endif  //not MINIMAL

/*
For implementing Post/Redirect/Get (PRG)
See: https://en.wikipedia.org/wiki/Post/Redirect/Get
Based on:    CaptivePortal(void)
*/
void webRedirect(const char* location){		
   Webserver->sendHeader(F("Location"), String(location), true);
   WSSend(303, CT_PLAIN, "");  // Empty content inhibits Content-length header so we have to close the socket ourselves.
   Webserver->client().stop();  // Stop is needed because we sent no content length
}


/***********************************************************************/
void WSTasPlusButton(const char* Action,const char* Text){
	  WSContentSend_P(PSTR(  
	   "<p><form action='%s' method='get'><button>%s</button></form></p>"
      ),Action,Text);
}//WSTasPlusButton

#ifdef SM_URF

#define WEB_DJLK		          "dj"
#define ID_DJLK_INTERVAL      "DI"
#define ID_UNITS              "IU"
#define ID_MM                 "IM"
#define ID_DISPLAY            "ID"
#define DIV_CALCULATE         "DC"

const char SCRIPT_CLICK_ENABLE[] PROGMEM = 
"function cen(){"                                          
    "eb('" DIV_CALCULATE "').style.display = eb('" DIV_ENABLE "').checked?'block':'none';"
"}"
"wl(cen);";

void HandleDJLKConfiguration(void){
  char parameter[FLOATSZ];

  if (!HttpCheckPriviledgedAccess()) { return; }

  AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_HTTP), PSTR(D_CONFIGURE_DJLK));

  if (Webserver->hasArg("save")) {
    DJLKSaveSettings();
    HandleConfiguration();
    //webRedirect(PSTR("/cn"));								//PRG to Config
    return;
  }

  WSContentStart_P(PSTR(D_CONFIGURE_DJLK));
  WSContentSend_P(SCRIPT_CLICK_ENABLE);
  WSContentSendStyle();
  htmlPageHeader(PSTR(D_CONFIGURE_DJLK));
  
  htmlTag(TM_START,TAG_FIELDSET);
   htmlTag(TM_STARTEND,TAG_LEGEND,nullptr,nullptr,PSTR("<b>&nbsp" D_CONFIGURE_DJLK "&nbsp;</b>")); 
   WSContentSend_P(PSTR(" <form method='post' action=''>"));   

    //Transmit interval
      htmlTag(TM_START,TAG_TABLE,nullptr,PSTR("width:100%%;border: 1px solid black;"));
		    htmlTag(TM_START,TAG_TR);
		      htmlTag(TM_START,TAG_TD,nullptr,PSTR("text-align:right;")); 
            WSContentSend_P(PSTR("Transmit updates every "));
		      htmlTag(TM_START,TAG_TD); 
            WSContentSend_P(PSTR("<input title='Set to 0 (zero) to disable all updates. Max.=255' type='number' id='" ID_DJLK_INTERVAL "' min='0' max='255' value='%u'>"),Settings.serial_delimiter);
		      htmlTag(TM_START,TAG_TD,nullptr,PSTR("text-align:left;")); 
            WSContentSend_P(PSTR("(seconds, approx.)"));
		    htmlTag(TM_START,TAG_TR);
		      WSContentSend_P(PSTR("<td colspan='3' style='text-align:center'>"));
            WSContentSend_P(PSTR("Set to 0 (zero) to disable all updates"));
      htmlTag(TM_END,TAG_TABLE);

    htmlTag(TM_START,TAG_BR);

    htmlTag(TM_START,TAG_FIELDSET);
     htmlTag(TM_STARTEND,TAG_LEGEND,nullptr,nullptr,PSTR("<b>&nbspCalculation&nbsp;</b>")); 
      WSContentSend_P(PSTR("<label id='ce' title='Click to Enable/Disable Calculation'>" ));  
        WSContentSend_P(PSTR("<input onclick='cen()' id='" DIV_ENABLE "' type='checkbox' %s><b>Enable Calculation?</b>"
	  	          ),(Settings.djlk_calculation.enabled?"checked":""));  
    	htmlTag(TM_END ,TAG_LABEL);

      htmlTag(TM_START,TAG_DIV,PSTR(DIV_CALCULATE ));

        htmlTag(TM_START,TAG_TABLE,nullptr,PSTR("width:100%%;border: 1px solid black;"));
		      htmlTag(TM_START,TAG_TR);
            WSContentSend_P(PSTR("<th style='text-align:center' rowspan='2'>"));
              WSContentSend_P(PSTR("Range<br>(mm)"));
            WSContentSend_P(PSTR("<th style='text-align:center' colspan='2'>"));
              WSContentSend_P(PSTR("Display"));
		      htmlTag(TM_START,TAG_TR);
  		      htmlTag(TM_START,TAG_TH,nullptr,PSTR("text-align:right"));
              WSContentSend_P(PSTR("Value"));
		        htmlTag(TM_START,TAG_TH,nullptr,PSTR("text-align:center")); 
             WSContentSend_P(PSTR("Units"));

		      for(uint i=0;i<MAX_CALCULATIONS;i++){
  		      htmlTag(TM_START,TAG_TR);
  		        htmlTag(TM_START,TAG_TD); 
                WSContentSend_P(PSTR(
                 "<input type='number' id='" ID_MM "%u' value='%u' title='0(zero)=ignore this row' style='width:7em' max='65535' min='0'>")
                 ,i,Settings.djlk_calculation.calPair[i].mm);
              htmlTag(TM_START,TAG_TD); 
                WSContentSend_P(PSTR(
                 "<input style='text-align:right' type='number' id='" ID_DISPLAY "%u' value='%u' max='65535' min='0'>")
                 ,i,Settings.djlk_calculation.calPair[i].value);
              if(!i){
                WSContentSend_P(PSTR("<td valign='middle' rowspan='%u'>"),MAX_CALCULATIONS);
                  WSContentSend_P(PSTR(
                "<input type='text' id='" ID_UNITS "' placeholder='e.g. litres  (%u chars max.)' value='%s' maxlength='%u' size='%u'>")
                 ,STRING_CALCULATION_UNITS-1,Settings.djlk_calculation.cUnits,STRING_CALCULATION_UNITS-1,STRING_CALCULATION_UNITS);
              }
          }
        htmlTag(TM_END,TAG_TABLE);

      htmlTag(TM_END,TAG_DIV);

    htmlTag(TM_END,TAG_FIELDSET);

  htmlTag(TM_END,TAG_FIELDSET);
      
  WSContentSend_P(HTTP_FORM_END);
	WSContentSpaceButton(BUTTON_CONFIGURATION);
  WSContentStop();
}//HandleDJLKConfiguration

/***********************************************************************/
void DJLKSaveSettings(void){
  char tmp[20];
  char webindex[20];
  djlk_calculation_pair_t calPair[MAX_CALCULATIONS];
  djlk_calculation_pair_t tempCalPair;

  snprintf_P(webindex, sizeof(webindex), PSTR("%s"),ID_DJLK_INTERVAL);
  WebGetArg(webindex, tmp, sizeof(tmp)); 
  Settings.serial_delimiter=atoi(tmp); 

  snprintf_P(webindex, sizeof(webindex), PSTR("%s"),DIV_ENABLE);
  Settings.djlk_calculation.enabled=Webserver->hasArg(webindex);

  snprintf_P(webindex, sizeof(webindex), PSTR("%s"),ID_UNITS);
  WebGetArg(webindex, Settings.djlk_calculation.cUnits, sizeof(Settings.djlk_calculation.cUnits));

  for(uint i=0;i<MAX_CALCULATIONS;i++){
    snprintf_P(webindex, sizeof(webindex), PSTR("%s%u"),ID_MM,i);
    WebGetArg(webindex, tmp, sizeof(tmp)); 
    calPair[i].mm = atoi(tmp);
    
    snprintf_P(webindex, sizeof(webindex), PSTR("%s%u"),ID_DISPLAY,i);
    WebGetArg(webindex, tmp, sizeof(tmp)); 
    calPair[i].value = atoi(tmp);
  }

  //Sort: largest to smallest, and remove same 'mm' entries
  bool bSorted = false;
  while(!bSorted){
    bSorted=true;
    for(uint i=1;i<MAX_CALCULATIONS;i++){
      if(calPair[i].mm>calPair[i-1].mm){
        tempCalPair  = calPair[i-1];
        calPair[i-1] = calPair[i];
        calPair[i]   = tempCalPair;
        bSorted=false;
      }
      if(calPair[i].mm){
        if(calPair[i].mm==calPair[i-1].mm){
          calPair[i].mm     = 0;
          calPair[i].value  = 0;
          bSorted=false;
        }
      } else {
        calPair[i].value  = 0;
      }
    }
  }

  for(uint i=0;i<MAX_CALCULATIONS;i++){
    Settings.djlk_calculation.calPair[i] = calPair[i];
  }
}//DJLKSaveSettings

int djlk_calculation(int imm){
  if(!Settings.djlk_calculation.enabled) return -999;

  //make sure there is at least 2 points
  uint8_t uNumPoints=0;
  
  for(uint i=0;i<MAX_CALCULATIONS;i++){
    if(Settings.djlk_calculation.calPair[i].mm){
      uNumPoints++;
    }
  }
  if(uNumPoints<2) return -999;
  
  //Workout which zone we are in
  // Assumes that calPair[] is sorted in decending order on .mm (done during save)
  /*         Zone 0
    mm[0] ----------------
             Zone 0
    mm[1] ----------------
             Zone 1
    mm[2] ----------------
             Zone 2
    mm[3] ----------------
             Zone 2
  */
  uint8_t uZone=0;  
  for(uint i=2;i<MAX_CALCULATIONS-1;i++){
    if(       Settings.djlk_calculation.calPair[i].mm &&
        imm > Settings.djlk_calculation.calPair[i].mm
      ){
      uZone=i-1;
    }
  }

  //Get slope of line
  int iDeltaX = Settings.djlk_calculation.calPair[uZone].mm - 
                Settings.djlk_calculation.calPair[uZone+1].mm;

  int iDeltaY = ((int)Settings.djlk_calculation.calPair[uZone].value) - 
                ((int)Settings.djlk_calculation.calPair[uZone+1].value);

  double dSlope;
  if(iDeltaX){
    dSlope = ((double)iDeltaY) / ((double)iDeltaX);
  } else {
    return -999;
  }
  //AddLog_P(LOG_LEVEL_INFO, PSTR("Zone:%u imm:%u DeltaY/X:%d/%d"),uZone,imm,iDeltaY,iDeltaX);	

  //Calculate 
  double dComputed = (dSlope * ((double)(imm-((int)Settings.djlk_calculation.calPair[uZone+1].mm))))
                     + 
                     Settings.djlk_calculation.calPair[uZone+1].value;
  return (int)dComputed;
}
#endif


/*********************************************************************************************\
 * Interface
\*********************************************************************************************/
#define SHORT_PRESS_MILLISEC 1000   //1 sec

bool Xdrv50(uint8_t function){
	
  bool result = false;    //true = call has been handled

  switch (function) {
#ifdef FIRMWARE_MINIMAL
    case FUNC_WEB_ADD_HANDLER:
      Webserver->on("/" WEB_HELP, HandleHelp);
      break;
    case FUNC_WEB_ADD_MAIN_BUTTON:											
      WSTasPlusButton(WEB_HELP	,D_HELP );
      break;
#else
#ifdef SP_STRIP
    case FUNC_BUTTON_PRESSED:
      static uint32_t buttonPressTimeMillisec = 0;
      static uint lastPowerState = POWER_OFF;
      // Called about every 250 ms
      // XdrvMailbox.index == 0 (Button 1)
      // XdrvMailbox.payload = 0=PRESSED Button down, 1=NOT_PRESSED=Button up.
      if (0==XdrvMailbox.index && 
        XdrvMailbox.payload !=Button.last_state[XdrvMailbox.index]){
          if(PRESSED==XdrvMailbox.payload){
            buttonPressTimeMillisec = millis();
          } else {
            if((millis()-buttonPressTimeMillisec) <= SHORT_PRESS_MILLISEC){
              uint newPowerState = lastPowerState == POWER_OFF?POWER_ON:POWER_OFF;
              for(uint i =1;i<=devices_present;i++)
                ExecuteCommandPower(i, newPowerState, SRC_BUTTON);
              lastPowerState = newPowerState;
            }
          }
          return true;
      } 
      break;
#endif
    case FUNC_WEB_ADD_MAIN_BUTTON:											
      WSTasPlusButton(WEB_HELP	,D_HELP );
      break;

    case FUNC_WEB_ADD_HANDLER:
      Webserver->on("/" WEB_HELP, HandleHelp);

#ifdef MAX_WATCHDOGS
      Webserver->on("/" WEB_WATCHDOG, HandleWatchdog);
#else
      Webserver->on("/" WEB_DJLK,HandleDJLKConfiguration);
#endif
      break;

    case FUNC_WEB_ADD_BUTTON:											
#ifdef SM_URF
      WSTasPlusButton(WEB_DJLK    	,D_CONFIGURE_DJLK);
#else
      WSTasPlusButton(WEB_WATCHDOG	,D_WATCHDOG);
#endif
      break;

#ifdef MAX_WATCHDOGS
    case FUNC_EVERY_SECOND:
		  WatchdogEvery1Sec();
      if(Rtc.utc_time%4==0){	
		   WatchdogEvery4Sec();
      }
	    break;
#endif

#endif
	  	  
  }
  return result;
}//Xdrv50
