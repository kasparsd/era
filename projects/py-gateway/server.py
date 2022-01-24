import logging

import mysensors.mysensors as mysensors

logging.basicConfig(level=logging.DEBUG)

def event(message):
    """Callback for mysensors updates."""
    print('sensor_update ' + message)

GATEWAY = mysensors.SerialGateway(
	'/dev/tty.usbserial-1410', 
	baud = 9600, 
	event_callback = event,
	protocol_version = '2.2'
)

GATEWAY.debug = True
GATEWAY.start()
