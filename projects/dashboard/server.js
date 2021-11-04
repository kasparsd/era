const modbus = require('modbus-stream');

modbus.serial.connect(
    '/dev/tty.usbserial-1420',
    {
        debug: true
    },
    (err, connection) => {
        if (err) throw err;
    }
);
