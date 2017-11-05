
#include "gogu.h"

/* Don't hardwire the IP address or we won't get the benefits of the pool.
 *  Lookup the IP address for the host name instead */
IPAddress timeServerIP; // time.nist.gov NTP server address
//const char* ntpServerName = "time.nist.gov";
const char* ntpServerName = "nsath.forthnet.gr";
const int NTP_PACKET_SIZE = 48;		// NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets
unsigned int localPort = 2390;      // local port to listen for UDP packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;



boolean gogu_ReturnCurentHour(S_DATA_STRUCT *time)
{
	boolean lu8_returnValue = 0;
	byte lu8_count = 0;
	int cb = 0;

	while((!cb) && (lu8_count < 3))
	{
		//get a random server from the pool
		WiFi.hostByName(ntpServerName, timeServerIP);
		Serial.print("NTP Server : ");
		Serial.println(ntpServerName);

		sendNTPpacket(timeServerIP); // send an NTP packet to a time server
		// wait to see if a reply is available
		delay(1000);

		cb = udp.parsePacket();
		lu8_count= lu8_count + 1;
	}

	if (!cb) {
		Serial.println("no packet yet");
		return 0;
	}
	else {
		//    // We've received a packet, read the data from it
		udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

		//the timestamp starts at byte 40 of the received packet and is four bytes,
		// or two words, long. First, esxtract the two words:

		unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
		unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
		// combine the four bytes (two words) into a long integer
		// this is NTP time (seconds since Jan 1 1900):
		unsigned long secsSince1900 = highWord << 16 | lowWord;
		Serial.print("Seconds since Jan 1 1900 = " );
		Serial.println(secsSince1900);

		// now convert NTP time into everyday time:
		// Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
		const unsigned long seventyYears = 2208988800UL;
		// subtract seventy years:
		unsigned long epoch = secsSince1900 - seventyYears;

		int UTC_hour 	= (epoch  % 86400L) / 3600;
		int UTC_min		= (epoch  % 3600) / 60;

		time->hour = UTC_hour + 2;
		time->minutes = UTC_min;
		lu8_returnValue = 1;

	}

	return lu8_returnValue;

}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress& address)
{
	//  Serial.println("sending NTP packet...");
	// set all bytes in the buffer to 0
	memset(packetBuffer, 0, NTP_PACKET_SIZE);
	// Initialize values needed to form NTP request
	// (see URL above for details on the packets)
	packetBuffer[0] = 0b11100011;   // LI, Version, Mode
	packetBuffer[1] = 0;     // Stratum, or type of clock
	packetBuffer[2] = 6;     // Polling Interval
	packetBuffer[3] = 0xEC;  // Peer Clock Precision
	// 8 bytes of zero for Root Delay & Root Dispersion
	packetBuffer[12]  = 49;
	packetBuffer[13]  = 0x4E;
	packetBuffer[14]  = 49;
	packetBuffer[15]  = 52;

	// all NTP fields have been given values, now
	// you can send a packet requesting a timestamp:
	udp.beginPacket(address, 123); //NTP requests are to port 123
	udp.write(packetBuffer, NTP_PACKET_SIZE);
	udp.endPacket();
}
