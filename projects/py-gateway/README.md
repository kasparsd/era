# Python MySensors Gateway

Using the [pymysensors](https://github.com/theolind/pymysensors) CLI:

	pymysensors --debug serial-gateway --port /dev/tty.usbserial-1420 --baud 9600 --persistence --protocol_version 2.2

or using the `server.py`:

	pip install -r requirements.txt
	python server.py

Adjust the serial port path to match the actual port. See this [full example used by `pymysensors` CLI](https://github.com/theolind/pymysensors/blob/41d002b5c9f4b2594147b72178de2fc2293fdb89/mysensors/cli/gateway_serial.py) for reference.
