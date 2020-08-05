// Nombre : María Claudia Pérez Escalante
// correo : mariaclaudiaperezes@gmail.com
// DNI: 95.962.971

#ifndef terminal_formats
  #define terminal_formats
  #ifdef terminal_formats_active
    #define MAGENTA_C  "\x1b[35m"
    #define RED_C    "\x1b[31m"
    #define BOLD_W "\x1b[1m"
    #define NORMAL_W "\x1b[m"
    #define WHITE_B   "\x1b[47m"
    #define DEFAULT_C "\x1b[39m"
    #define BLACK_C "\x1b[30m"
    #define DEFAULT_B "\x1b[49m"
    #define BLUE_C "\x1b[34m"
    #define COLOR_198 "\x1b[38;5;198m"
    #define COLOR_11 "\x1b[38;5;11m"
    #define COLOR_10 "\x1b[38;5;10m"
    #define COLOR_202 "\x1b[38;5;202m"
    #define COLOR_172 "\x1b[38;5;172m"
    #define COLOR_14 "\x1b[38;5;14m"
    #define COLOR_118 "\x1b[38;5;118m"
    #define COLOR_131 "\x1b[38;5;131m"
    #define COLOR_83 "\x1b[38;5;83m"
    #define COLOR_170 "\x1b[38;5;170m"
    #define COLOR_149 "\x1b[38;5;149m"
    #define COLOR_30 "\x1b[38;5;30m"
    #define BLINK "\x1b[5m"
    #define COLOR_226 "\x1b[38;5;226m"
    #define COLOR_46 "\x1b[38;5;46m"
    #define COLOR_220 "\x1b[38;5;220m"
    #define BACKGROUND_RED "\x1b[101m"
    #define WHITE "\x1b[97m"
  #else
    #define MAGENTA_C  ""
    #define RED_C ""
    #define BOLD_W ""
    #define NORMAL_W ""
    #define WHITE_B ""
    #define DEFAULT_C ""
    #define BLACK_C ""
    #define DEFAULT_B ""
    #define BLUE_C ""
    #define COLOR_198 ""
    #define COLOR_10 ""
    #define COLOR_14 ""
    #define COLOR_11 ""
    #define COLOR_202 ""
    #define COLOR_172 ""
    #define COLOR_118 ""
    #define COLOR_131 ""
    #define COLOR_83 ""
    #define COLOR_170 ""
    #define COLOR_149 ""
    #define COLOR_30 ""
    #define COLOR_226 ""
    #define BLINK ""
    #define COLOR_46 ""
    #define COLOR_220 ""
    #define BACKGROUND_RED ""
  #endif

  #ifdef __unix__ //para resetear la consola
    #define clear system("clear")
  #elif 
    #define clear system("cls")
  #endif
#endif