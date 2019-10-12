

void setup() {
    Serial.begin( 115200 );
    pinMode( 13, INPUT_PULLUP );
    pinMode( 12, OUTPUT );
    pinMode( 11, INPUT_PULLUP );
    digitalWrite( 12, HIGH );
}

bool SyncBehavior() {
    static uint8_t byte = 0, shift = 0;
    static uint8_t lastBit = 0, matched = 0, syncIn = 0x5a, syncOut = 0xa5;
    static bool syncing = false, synced = false;

    while( digitalRead( 13 ) ) {
        ;;
    }

    lastBit = digitalRead( 11 );
    byte |= lastBit << ( 7 - shift );
    shift++;

    if ( lastBit != ( ( syncIn >> ( 7 - matched ) ) & 0x01 ) ) {
        matched = 0;
        syncing = false;
        digitalWrite( 12, HIGH );
    } else {
        matched++;
    }
    
    if ( matched > 7 ) {
        matched = 0;
        byte = 0x5a;
        shift = 0;
        if ( syncing ) {
            synced = true;
            //Serial.print("synced!\n");
        } else {
            syncing = true;
            //Serial.print("sync\n");
        }

    }
    
    if ( shift > 7 ) {
        shift = 0;
        //Serial.print( byte, HEX );
        byte = 0;
    }
    while( ! digitalRead( 13 ) ) {
        ;;
    }
    if ( syncing ) {
        digitalWrite( 12, ( ( ( syncOut >> ( 7 - matched ) ) & 0x01 ) == 0 ) ? LOW : HIGH );
    }
    if ( synced ) {
        digitalWrite( 12, LOW );
    }

    return synced;
}

void DumpBehavior() {
    static uint8_t byte = 0, shift = 0;

    while( digitalRead( 13 ) ) {
        ;;
    }

    byte |= digitalRead( 11 ) << ( 7 - shift );
    shift++;
    
    if ( shift > 7 ) {
        Serial.write( byte );
        shift = 0;
        byte = 0;
    }
    while( ! digitalRead( 13 ) ) {
        ;;
    }
}

void loop() {
    static bool synced = false;

    if ( !synced ) {
        synced = SyncBehavior();
    } else {
        DumpBehavior();
    }
}