import redis
r = redis.Redis(host='192.168.101.108', port=6379, db=0)
command = "HMGET %s stat"%("name_plate_det_key")
#reply = r.hmget(command)

loc_dict = {}

#INST_VOLT_R

loc_dict = r.hgetall("inst_info")

#print loc_dict["INST_CUR_IY"]
#nname_plate_str = {}
print r.hmget("inst_info","INST_VOLT_R")


#print reply.element[0].str
#print len(reply)
#print (reply)

'''reply = redisCommand(c, "HMGET %s stat", "mykey");
	mytest* response = reply->element[0]->str;
	printf("status %d %ld, test4 : %d\n", response->myInt, response->myLong, response->sub_struct.test4);
	freeReplyObject(reply);'''
