// unix_local.h: Unix-specific Quake3 header file

void Sys_QueEvent( int time, sysEventType_t type, int value, int value2, int ptrLength, void *ptr );
qboolean Sys_GetPacket ( netadr_t *net_from, msg_t *net_message );
void Sys_SendKeyEvents (void);

// Input subsystem

void IN_Init (void *windowData);
void IN_Frame (void);
void IN_Shutdown (void);
void IN_Restart( void );


void IN_JoyMove( void );
void IN_StartupJoystick( void );

// GL subsystem
qboolean QGL_Init( const char *dllname );
void QGL_EnableLogging( qboolean enable );
void QGL_Shutdown( void );





// bk001130 - win32
// void IN_JoystickCommands (void);

char *strlwr (char *s);
