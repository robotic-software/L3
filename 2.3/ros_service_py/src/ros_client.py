#!/usr/bin/env python

import sys
import rospy
from ros_service_py.srv import service

def ros_service_client(message):
    print("Attendo la connessione al server")
    rospy.wait_for_service('service')
    try:
        serv = rospy.ServiceProxy('service', service)
        resp1 = serv(message)

        return resp1.out

    except rospy.ServiceException as e:
        print("Service call failed: %s"%e)

def usage():
    return "USAGE: %s [message]"%sys.argv[0]

if __name__ == "__main__":
    if len(sys.argv) == 2:
        message = str(sys.argv[1])        
    else:
        print(usage())
        sys.exit(1)

    print("Requesting %s"%(message))
    #print("returning %s"%(message, ros_service_client(message)))
    print(ros_service_client( message ) )