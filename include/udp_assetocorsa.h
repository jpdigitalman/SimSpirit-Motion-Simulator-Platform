struct RTCarInfo{
	char identifier;
	int size;
	float speed_Kmh;
	float speed_Mph;
	float speed_Ms;
	bool isAbsEnabled;
	bool isAbsInAction;
	bool isTcInAction;
	bool isTcEnabled;
	bool isInPit;
	bool isEngineLimiterOn;
	float accG_vertical;
	float accG_horizontal;
	float accG_frontal;
	int lapTime;
	int lastLap;
	int bestLap;
	int lapCount;
	float gas;
	float brake;
	float clutch;
	float engineRPM;
	float steer;
	int gear;
	float cgHeight;
	float wheelAngularSpeed[4];
	float slipAngle[4];
	float slipAngle_ContactPatch[4];
	float slipRatio[4];
	float tyreSlip[4];
	float ndSlip[4];
	float load[4];
	float Dy[4];
	float Mz[4];
	float tyreDirtyLevel[4];
	float camberRAD[4];
	float tyreRadius[4];
	float tyreLoadedRadius[4];
	float suspensionHeight[4];
	float carPositionNormalized;
	float carSlope;
	float carCoordinates[3];
} ;

struct RTLap{
	int carIdentifierNumber;
	int lap;
	char driverName[50];
	char carName[50];
	int time;

};

struct Result{
    bool result;
    RTCarInfo carInfo;
    RTLap lap;
};

struct handshaker{
    int identifier;
    int version;
    int operationId;
};

struct handshackerResponse{
    char carName[50];
    char driverName[50];
    int identifier;
    int version;
    char trackName[50];
    char trackConfig[50];
};

handshaker hand = {1, 1, 0};
handshaker update = {1, 1, 1};
handshaker spot = {1, 1, 2};
handshaker quit = {1, 1, 3};
handshackerResponse tmpHandshake;

bool isUpdate;
/// @brief //
////

void sendHandshake(){
	udp.beginPacket();
	uint8_t b[sizeof(hand)];
	memcpy(b, &hand, sizeof(hand));
	udp.write(b, sizeof(hand));
	udp.endPacket();

	//receive
	uint8_t buffer[sizeof(tmpHandshake)];
	memset(buffer, 0, sizeof(tmpHandshake));
	udp.parsePacket();
	if(udp.read(buffer, sizeof(tmpHandshake)) == sizeof(tmpHandshake)){
		memcpy(&tmpHandshake, buffer, sizeof(tmpHandshake));
		Serial.println();
	}

	else
	    Serial.println("Error, no Handshake received!");
}

void sendUpdate(){
	udp.beginPacket();
	uint8_t b[sizeof(update)];
	memcpy(b, &update, sizeof(update));
	udp.write(b, sizeof(update));
	udp.endPacket();
	isUpdate = true;
}

void sendSpot(){
	udp.beginPacket();
	uint8_t b[sizeof(spot)];
	memcpy(b, &update, sizeof(spot));
	udp.write(b, sizeof(spot));
	udp.endPacket();
	isUpdate = false;
}


void sendQuit(){
	udp.beginPacket();
	uint8_t b[sizeof(quit)];
	memcpy(b, &update, sizeof(quit));
	udp.write(b, sizeof(quit));
	udp.endPacket();
}


Result readUpdate(){
    Result result;
    uint8_t buffer[sizeof(result.carInfo)];
    memset(buffer, 0, sizeof(result.carInfo));
    udp.parsePacket();
    if(udp.read(buffer, sizeof(result.carInfo)) == sizeof(result.carInfo)){
        memcpy(&result.carInfo, buffer, sizeof(result.carInfo));
        result.result = isUpdate;
        memset(&result.lap, 0, sizeof(result.lap));
        return result;
    }

    else{
        result.result = isUpdate;
        memset(&result.carInfo, 0, sizeof(result.carInfo));
        memset(&result.lap, 0, sizeof(result.lap));
        return result;
    }
}


Result readSpot(){
    Result result;
    uint8_t buffer[sizeof(result.lap)];
    memset(buffer, 0, sizeof(result.lap));
    udp.parsePacket();
    if(udp.read(buffer, sizeof(result.lap)) == sizeof(result.lap)){
        memcpy(&result.lap, buffer, sizeof(result.lap));
        result.result = isUpdate;
        memset(&result.carInfo, 0, sizeof(result.carInfo));
        return result;
    }

    else{
        result.result = isUpdate;
        memset(&result.carInfo, 0, sizeof(result.carInfo));
        memset(&result.lap, 0, sizeof(result.lap));
        return result;
    }
}

Result read(){
    if (isUpdate) return readUpdate();

    else return readSpot();
}

void setupAssetoCorsa(){
  
  //send the handshake to Assetto Corsa
  sendHandshake();
  
  // use sendUpdate if the client wants to be updated from the specific ACServer.
  sendUpdate();
  
  // use sendSpot if the client wants to be updated from the specific 
  // ACServer just for SPOT Events (e.g. the end of a lap). using:
  
  //sendSpot();
  
  // use sendQuit if the client wants to leave the communication with ACServer.
  //using:
  
  //sendQuit();
}

void readAssetoCorsa(){
    Result carInfo; //create a struct to save all the data
    carInfo = read(); //save on the new struct all the data returned by read

    if (carInfo.result){
		//carInfo.l

    }
    else
        Serial.println("Spot!");
}
