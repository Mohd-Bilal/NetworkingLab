import socket,sys
from struct import *


s_tcp = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_TCP)
s_udp = socket.socket(socket.AF_INET,socket.SOCK_RAW,socket.IPPROTO_UDP)

filt = sys.argv[1]
filt = filt.lower()

while True:
  packet = s_tcp.recvfrom(65565) if filt.lower()=="tcp" else s_udp.recvfrom(65565)
  packet = packet[0]
  ip_header = packet[0:20]
  iph = unpack('!BBHHHBBH4s4s',ip_header)
  version_ihl = iph[0]
  version =     version_ihl>>4
  ihl = version_ihl&0xF

  iph_length = ihl*4
  ttl = iph[5]
  protocol = iph[6]
  s_addr = socket.inet_ntoa(iph[8])
  d_addr = socket.inet_ntoa(iph[9])
  print("\n---------------------PACKET BEGIN----------------------------")
  print("Version :",str(version),"\nIP Header Length :",str(ihl),"\nTTL",str(ttl),"\nProtocol :",str(protocol),"\nSource Address :",str(s_addr),"\nDestination Address :",str(d_addr))
  if filt == "tcp":
      tcp_header = packet[iph_length:iph_length+20]
      tcph = unpack('!HHLLBBHHH' , tcp_header)
      source_port = tcph[0]
      dest_port = tcph[1]
      sequence = tcph[2]
      acknowledgement = tcph[3]
      doff_reserved = tcph[4]
      tcph_length = doff_reserved>>4
      print("\n-------------------------------TCP HEADER---------------------------------") 
      print("Source Port :",str(source_port),"\nDestination Port :",str(dest_port),"\nSequence Number :",str(sequence),"\nAcknowledgement :",str(acknowledgement),"\nHeader Length :",str(tcph_length))
      print("\n---------------------PACKET END--------------------------------")
  else:
      udp_header = packet[iph_length:iph_length+8]
      udph = unpack('!HHHH',udp_header)
      source_port = udph[0]
      dest_port = udph[1]
      length = udph[2]
      checksum = udph[3]
      print("\n----------------------------UDP Header---------------------------")
      print("Source Port :",str(source_port),"\nDestination Port :",str(dest_port),"\nLength :",str(length),"\nChecksum :",str(checksum))
      print("\n----------------------PACKET END------------------------------")