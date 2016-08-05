#include "contiki.h"
#include "net/tcpip.h"
#include "dev/leds.h"
#include "networking/networking.h"

#include <stdio.h>

#include "TinyIPFIX/tinyipfix.h"

struct template_rec *sky_rec;

PROCESS(main_proc, "Main Process");
AUTOSTART_PROCESSES(&main_proc);

PROCESS_THREAD(main_proc, ev, data)
{

  // Process data declaration
  static struct etimer timer;
  uint8_t *buffer;
  PROCESS_BEGIN();

  if(conn_set_up() == -1) {
	  PROCESS_EXIT();
  }


  initialize();


  // Set event timers for template and data packet creation
  etimer_set (&timer, CLOCK_SECOND);

  while (1) {

	  PROCESS_WAIT_EVENT();
      if (etimer_expired (&timer)) {

    	  //buffer = get_template();

    	  buffer = get_data();

    	  leds_on (LEDS_GREEN);
    	  clock_delay (500);
    	  leds_off (LEDS_GREEN);

    	  send_data(buffer,50);

    	  etimer_reset (&timer);
      }
  }

  PROCESS_END();
}


