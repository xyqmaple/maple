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
	//2.׼��ͨ�ŵ�ַ��ʹ�ýṹ������
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.s_addr = inet_addr("172.30.3.105");
	//3.��socket��ͨ�ŵ�ַ��ʹ��bind()
	int res = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	if(-1 == res)
	{
		perror("bind"),exit(-1);
	}
	printf("�󶨳ɹ�\n");
	//4.����ͨ�ţ�send()/sendto()/recv/recvfrom
	char buf[100] = {0};
	//׼���ṹ������ʹ�С�ı���
	struct sockaddr_in recv_addr;
	socklen_t len = sizeof(recv_addr);
	//res = recv(socket, buf, sizeof(buf), 0);
	res = recvfrom(socket, buf, sizeof(buf), 0, (struct sockaddr*)&recv_addr, &len);
	if(-1 == res)
	{
		perror("recvfrom"),exit(-1);
	}
	printf("�ͻ��˷����������ǣ�%s,���ݴ�С��:%d\n", buf, res);
	//���ʵ����ͻ��˻ط���Ϣ��???
	res = sendto(sockfd, "I received!", 11, 0, (struct sockaddr*)&recv_addr, len);
	if(-1 == res)
	{
		perror("sendto"),exit(-1);
	}
	printf("�ɹ��������ݵ��ͻ��ˣ����͵����ݴ�С�ǣ�%d\n", res);
	//5.�ر�socket,ʹ��close()
	res = close(sockfd);
	if(-1 == res)
	{
		perror("close"),exit(-1);
	}
	printf("�ɹ��ر�socket\n");
	return 0;
}









