#!/usr/bin/env python

from ros_service_py.srv import service, serviceResponse
import rospy

def service_callback(req):
    print( req )
    #print("Returning [%s + %s = %s]"%(req.a, req.b, (req.a + req.b)))
    return serviceResponse("prova riuscita")
    print("qui")

def service_server():
    print("In service server")
    rospy.init_node('service_server')
    s = rospy.Service('service', service, service_callback)

    rospy.spin()
    
if __name__ == "__main__":
    service_server()