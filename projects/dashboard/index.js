const ModbusRTU = require('modbus-serial');
const client = new ModbusRTU();

const toUint16 = (string) => new Uint16Array(new TextEncoder('utf-8').encode(string));

const wifiCredentials = {
    ssid: 'YOURSSID',
    password: 'YOURPASSWORD'
};

client.connectRTUBuffered(
    '/dev/tty.usbserial-1410', 
    { 
        baudRate: 9600 
    }
).then( async () => {
    client.setID(1);

    await client.writeRegisters(30, toUint16(wifiCredentials.ssid))
        .then(() => {
            return client.readHoldingRegisters(30, 20)
                .then(val => {
                    console.log( 'got', val.buffer.toString() )
                });
        });
    
    await client.writeRegisters(10, toUint16(wifiCredentials.password))
        .then(() => {
            return client.readHoldingRegisters(10, 20)
                .then(val => {
                    console.log( 'got', val.buffer.toString() )
                });
        });

    return client.writeCoil(10, true).then( r => console.log(r) );
} ).catch( err => console.error( err ) );