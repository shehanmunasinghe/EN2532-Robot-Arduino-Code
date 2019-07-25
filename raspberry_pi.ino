void init_rpi(){
    Serial3.println("");Serial3.println("READY");Serial3.println("");
}

int detect_coin_color(){
    // Serial2.println("detect_coin_color");

    Serial3.println("");Serial3.println("DETECT");Serial3.println("");    
    
    unsigned long start_time=millis();
    int timeout=10000; //Assume a single revo takes ~1 millisecond. Timeout is 3 times that
    while (!Serial3.available()) {
        unsigned long current_time=millis();
        if((current_time-start_time)>timeout){
            Serial2.println("Timeout");
            break;
            // return; 
        }
    }
    if(Serial3.available()){
        char c = Serial3.read();
        Serial2.println(c);

        switch (c){
            case 'R':
                Serial2.println("COIN_COLOR_RED");
                return COIN_COLOR_RED;
                break;
            case 'G':
                Serial2.println("COIN_COLOR_GREEN");
                return COIN_COLOR_GREEN;
                break;
            case 'B':
                Serial2.println("COIN_COLOR_BLUE");
                return COIN_COLOR_BLUE;
                break;            
            default:
                Serial2.println("Error-unhandled color");
                //TODO - ADD default color
                break;
        }
    }

    Serial2.println("Error-serial error");

}

void test_rpi_conn(){
    if(Serial3.available()){
        char c = Serial3.read();
        Serial2.println(c);
    }
}