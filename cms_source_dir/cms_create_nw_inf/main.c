#include <stdio.h>
#include <string.h>

char line[128];

void createNetworkFile(char *ipAddr,char *netMask, char *gw,char *interface)
{
	FILE *fp1, *fp2;
	int routeAdded = 0;
	int infFound = 0;
	
	fp1 = fopen("/etc/network/interfaces","r");
	if ( fp1 == NULL )
	{
		printf("Failed open bs file\n");
		return;
	}
	
	fp2 = fopen("/etc/network/interfaces1","w");
	if ( fp2 == NULL )
	{
		printf("Failed open bs file for writing\n");
		fclose(fp1);
		return;
	}
	
	memset(line,0,128);
	while ( fgets(line,128,fp1) != NULL )
	{
		if ( strstr(line,"auto") != NULL ) 
		{
			printf("auto key word found\n");
			if ( strstr(line,interface ) != NULL )
			{
				printf("Found the interface to be modified\n");
				infFound = 1;
			}
			else
				infFound = 0;
		}
		if ( infFound != 1 )
		{
			fprintf(fp2,line);
			memset(line,0,128);
			continue;

		}
		if (( strstr(line,"address") != NULL ) && ( strstr(line,"ether" ) == NULL ))
		{
			printf("IP Address\n");	
		//	memset(newLine,0,128);
			fprintf(fp2,"\taddress %s\n",ipAddr);
		} 
		else
		if ( strstr(line,"netmask") != NULL )
		{
			printf("Netmask\n");
			fprintf(fp2,"\tnetmask %s\n",netMask);	
		}
		else
		if ( strstr(line,"gateway") != NULL ) 
		{
			printf("GATEWAY\n");	
		//	memset(newLine,0,128);
			if ( strcmp(gw,"0.0.0.0") == 0 )
				fprintf(fp2,"#\n");
			else
				fprintf(fp2,"\tgateway %s\n",gw);

			routeAdded = 1;
		} 
		else
			fprintf(fp2,line);

		printf("line %s\n",line);
		memset(line,0,128);
	}
	if ( !routeAdded )
	{
		if ( strcmp(gw,"0.0.0.0") == 0 )
			fprintf(fp2,"#\n");
		else
			fprintf(fp2,"\n\tgateway %s\n",gw);
	}
	fclose(fp2);
	fclose(fp1);
}

int main(int argc , char *argv[])
{
	char paramList[4][32];

	printf("Num arg %d\n",argc);
	if ( argc < 5 )
	{
		printf("Invalid number of parameters\n");
		printf("Usage : createNetworkInf ipAddr subnetMask gwIpAddr interface\n");
		return -1;
	}
	
	memset(paramList[0],0,32);
	memcpy(paramList[0],argv[1],32);
	
	memset(paramList[1],0,32);
	memcpy(paramList[1],argv[2],32);

	memset(paramList[2],0,32);
	memcpy(paramList[2],argv[3],32);

	memset(paramList[3],0,32);
	memcpy(paramList[3],argv[4],32);

	printf("IP  : %s\n",paramList[0]);
	printf("Subnet  : %s\n",paramList[1]);
	printf("GW IP  : %s\n",paramList[2]);
	printf("Interface  : %s\n",paramList[3]);
	
	createNetworkFile(paramList[0],paramList[1],paramList[2],paramList[3]);
	
	return 0;
}
