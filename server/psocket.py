import socket
import os
import time

if __name__ == '__main__':


    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(("localhost", 8000))
    server.listen(0)



    while True:
        time_start=time.time()
        connection, address = server.accept()
        print(connection, address)
        recv_str = connection.recv(40000)

        recfilename = 'hello.exe'
        recfile = open(recfilename, mode="wb+")
        connection.send(bytes("hello client!\n",encoding="ascii"))
        reflag=True
        count=0;
        while(reflag) :
            recv_str = connection.recv(40000)
            count+=len(recv_str)
            #print(count)
            #recfile.write(recv_str)
            connection.send(bytes(len(recv_str)))
            if(len(recv_str)==0):
                 #print( len(recv_str))
            #     connection.send(bytes("test: %s" % len(recv_str), encoding="ascii"))
                 reflag=False

        recfile.close()
        time_end=time.time()

        print(time_end-time_start)

    time.sleep(0.5)
    connection.close()
    #input()
    """
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(("localhost", 8888))
    server.listen(0)
    while True:
        connection, address = server.accept()
        print(connection, address)
        recv_str=connection.recv(1024)[0:5]
        #recv_str=str(recv_str)  这样不行带有了b''
        recv_str=recv_str.decode("ascii")
        print( recv_str,len(recv_str) )
        connection.send( bytes("test: %s" % recv_str,encoding="ascii") )
        time.sleep( 0.5 )
    connection.close()
    input()
    """
