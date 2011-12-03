//Harvie 2o11 - Warning: Not bulletproof yet!
#define ENV_PREFIX "JAIL_"
#define DEFAULT_JAIL "/var/ssh-chroot"

#include <stdio.h>
#include <stdlib.h>

#define PAM_SM_SESSION
#include <security/pam_modules.h>

PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
	const char* user;
	pam_get_user(pamh, &user, "login: ");
	//printf("Welcome %s\n", user);

	setenv(ENV_PREFIX "USER", user, 1);
	setenv(ENV_PREFIX "DIR", DEFAULT_JAIL, 1);
	if(argc > 0) setenv(ENV_PREFIX "DIR", argv[0], 1);


	//system("echo start $HOME; echo a && true && echo b && false && echo c");
	setuid(0); setgid(0);
	system("mkdir -p \"$JAIL_DIR/$JAIL_USER/$JAIL_USER\"");
	system("chown root:root \"$JAIL_DIR/$JAIL_USER\"");
	system("chown \"$JAIL_USER:$JAIL_USER\" \"$JAIL_DIR/$JAIL_USER/$JAIL_USER\"");
	system("mountpoint -q \"$JAIL_DIR/$JAIL_USER/$JAIL_USER\" || mount -o bind \"$HOME\" \"$JAIL_DIR/$JAIL_USER/$JAIL_USER\"");

	return PAM_SUCCESS; //PAM_SESSION_ERR | PAM_SUCCESS
}
