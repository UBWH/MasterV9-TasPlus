/************************************************
support_tasplus.ino

Support for issuing HTML tags
************************************************/

enum tagmode_t{TM_START,TM_END,TM_STARTEND}; 
enum tag_t{TAG_DIV,TAG_TABLE,TAG_TR,TAG_TD,TAG_TH,TAG_SCRIPT,TAG_LEGEND,TAG_BR,TAG_FIELDSET,TAG_LABEL,TAG_SELECT}; 

const char HTTP_DIV[]      	PROGMEM = "div";
const char HTTP_TABLE[]    	PROGMEM = "table";
const char HTTP_TR[]    	  PROGMEM = "tr";
const char HTTP_TD[]    	  PROGMEM = "td";
const char HTTP_TH[]    	  PROGMEM = "th";
const char HTTP_SCRIPT[]   	PROGMEM = "script";
const char HTTP_LEGEND[]   	PROGMEM = "legend";
const char HTTP_BR[]       	PROGMEM = "br";
const char HTTP_FIELDSET[] 	PROGMEM = "fieldset";
const char HTTP_LABEL[]    	PROGMEM = "label";
const char HTTP_SELECT[]    PROGMEM = "select";


void htmlTag(	tagmode_t 	mode, 
				tag_t 		tag, 
				const char* id			  =nullptr, 
				const char* style		  =nullptr,
				const char* innerHTML	=nullptr,
				const char* title		  =nullptr
			){
  const char* t;
  
  switch(tag){
	case TAG_DIV:      	t=HTTP_DIV;      break;
	case TAG_TABLE:    	t=HTTP_TABLE;    break;
	case TAG_TR: 		    t=HTTP_TR; 		   break;
	case TAG_TD: 		    t=HTTP_TD; 		   break;
	case TAG_TH: 		    t=HTTP_TH; 		   break;
	case TAG_SCRIPT:   	t=HTTP_SCRIPT;   break;
	case TAG_LEGEND:   	t=HTTP_LEGEND;   break;
	case TAG_BR:       	t=HTTP_BR;       break;
	case TAG_FIELDSET: 	t=HTTP_FIELDSET; break;
	case TAG_LABEL:    	t=HTTP_LABEL;    break;
  case TAG_SELECT:    t=HTTP_SELECT;   break;
  
	
	default:
		return;
  }
  if(mode==TM_START || mode==TM_STARTEND){
	WSContentSend_P(PSTR("<%s"),t);
	if(id)   WSContentSend_P(PSTR(" id='%s'")   ,id);
    if(style)WSContentSend_P(PSTR(" style='%s'"),style);
	if(title)WSContentSend_P(PSTR(" title='%s'"),title);
	WSContentSend_P(PSTR(">"));
    if(innerHTML){WSContentSend_P(innerHTML);}
  } 
  
if(mode==TM_END || mode==TM_STARTEND){
 	WSContentSend_P(PSTR("</%s>"),t);
  }
}//htmlTag


void htmlPageHeader(const char* title){
   WSContentSend_P(PSTR("<h2 style='text-align:center'>%s</h2>"),title);
}//htmlPageHeader 


double CharToDouble(const char *str){
/*
Copied from xsns_53_sml.ino as Lat Long edits need this (Float causes rounding errors) 
*/
  // simple ascii to double, because atof or strtod are too large
  char strbuf[24];

  strlcpy(strbuf, str, sizeof(strbuf));
  char *pt = strbuf;
  while ((*pt != '\0') && isblank(*pt)) { pt++; }  // Trim leading spaces

  signed char sign = 1;
  if (*pt == '-') { sign = -1; }
  if (*pt == '-' || *pt=='+') { pt++; }            // Skip any sign

  double left = 0;
  if (*pt != '.') {
    left = atoi(pt);                               // Get left part
    while (isdigit(*pt)) { pt++; }                 // Skip number
  }

  double right = 0;
  if (*pt == '.') {
    pt++;
    right = atoi(pt);                              // Decimal part
    while (isdigit(*pt)) {
      pt++;
      right /= 10.0;
    }
  }

  double result = left + right;
  if (sign < 0) {
    return -result;                                // Add negative sign
  }
  return result;
}//CharToDouble

