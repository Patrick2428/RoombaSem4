#include "MQTTconfig.h"
#include <unistd.h>

static const int MAXSIZE_HOSTNAME{25};

const char *getHostname()
{
   /// @warning Array hostname has limited size.
   static char hostname[MAXSIZE_HOSTNAME] = {'\0'};
   gethostname(hostname, MAXSIZE_HOSTNAME);
   return hostname;
}
