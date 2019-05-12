//ʵ�ֻ���udpЭ�������ͨ��ģ��
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
	//1.����socket��ʹ��socket()
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(-1 == sockfd)
	{
		perror("socket"),exit(-1);
	}
	printf("����socket�ɹ�\n");
	//2.׼��ͨ�ŵ�ַ��ʹ�÷������ĵ�ַ
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.s_addr = inet_addr("172.30.3.105");
	//3.����ͨ�ţ�send()/sendto()/recv/recvfrom
	//int res = send(socket, "hello", 5, 0);
	int res = sendto(socket, "hello", 5, 0, (struct sockaddr*)&addr, sizeof(addr));
	if(-1 == res)
	{
		perror("sendto"),exit(-1);
	}
	printf("�ɹ��������ݵ������������͵����ݴ�С��:%d\n", res);
	//���ܷ������ط�����Ϣ
	char buf[100] = {0};
	res = recv(sockfd, buf, sizeof(buf), 0);
	if(-1 == res)
	{
		perror("recv"),exit(-1);
	}
	printf("��������������Ϣ�ǣ�%s����С�ǣ�%d\n", buf, res);
	//4.�ر�socket,ʹ��close()
	res = close(sockfd);
	if(-1 == res)
	{
		perror("close"),exit(-1);
	}
	printf("�ɹ��ر�socket\n");
	return 0;
}









