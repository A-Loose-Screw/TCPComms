#define BUFSIZE 512
#define PACKETSIZE sizeof(ItemStruct)


void serialize(ItemStruct *msgPacket, char *data) {
	int *q = (int*)data;	
	*q = msgPacket->value;	q++;	
	
	char *p = (char*)q;
	int i = 0;
	while (i < BUFSIZE) {
		*p = msgPacket->name[i];
		p++;
		i++;
	}
}

void deserialize(char *data, ItemStruct *msgPacket) {
	int *q = (int*)data;	
	msgPacket->value = *q;		q++;	
	
	char *p = (char*)q;
	int i = 0;
	while (i < BUFSIZE) {
		msgPacket->name[i] = *p;
		p++;
		i++;
	}
}