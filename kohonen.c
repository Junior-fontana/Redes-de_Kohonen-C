//Código-fonte extraído do livro:
/*
REDES NEURAIS - FUNDAMENTOS E APLICAÇÕES COM PROGRAMAS EM C.
AUTORES: LUDWIG, O; MONTGOMERY, E.
*/

#include <stdio.h>
#include <math.h>
#include <ncurses.h>
#include <stdlib.h>

#define nentrada 4
#define nneuronio 6 //Região retangular de 3 neurônios em cada linha.

#define nexemplos 10

int main()

{
	float w[nentrada][nneuronio], errodes, tau, sigma0, sigma, eta, eta0;
	int x, y, cont2, contt, epocas, k, l, k1, l1;
	float entradas[nentrada][nexemplos], teste[nentrada][6], d[nneuronio], l2, h, deucl;
	system("clear");
	for (x = 0;x<nentrada;x++)
	{
		for (y = 0; y<nneuronio; y++)
		{
			w[y][x] = rand()%2 + 0.5; 
		}
	}
	printf("Entre com o numero de epocas de treinamento: \n");
	scanf("%d",&epocas);
	printf("\nEntre com os valores de exemplo de treinamento de entrada: \n");
	for (x=0;x<nentrada;x++)
	{
		for (y=0;y<nexemplos;y++)
		{
			scanf("%f",&entradas[x][y]);
		}
	}
	printf("\nEntre com a taxa de aprendizado inicial: ");
	scanf("%f",&eta0);
	printf("\nErro desejado: ");
	scanf("%f",&errodes);
	printf("\nEntre com a largura efetiva inicial: ");
	scanf("%f",&sigma0);
	printf("\nConstante de tempo (tau): ");
	scanf("%f",&tau);
	system("clear");
	printf("Pesos iniciais: ");
	for (y=0;y<nentrada;y++)
	{
		for (x=0;x<nneuronio;x++)
		{
			printf("w[%d][%d] = %f\n",x,y,w[x][y]);
		}
	}
	printf("\nIniciando processo iterativo...\n");
	for (x = 0; x < epocas; x++)
	{
		for (y=0;y<nexemplos;y++)
		{
			for (contt=0;contt<nneuronio;contt++)
			{
				d[contt] = 0;
				for (cont2 = 0;cont2<nentrada;cont2++)
				{
					d[contt] = d[contt] + (entradas[cont2][y] - w[cont2][contt])*(entradas[cont2][y]-w[cont2][contt]); 
				}
			}
		}
	
	//Calcula a menor distância.
	deucl = d[0];
	for (contt=0;contt<nneuronio;contt++)
	{
		if (deucl >= d[contt])
		{
			deucl = d[contt];
		}
		if (deucl < d[contt])
		{
			break;
		}
	}
	for (contt = 0; contt < nneuronio;contt++)
	{
		if (deucl == d[contt])
		{
			k = (contt+1) % 3;
			if (k == 0)
			{
				k = 3;
			}
			l = 1 + contt /3;
			break;
		}
	}
	for (contt = 0;contt <nneuronio;contt++)
	{
		//Cálculo da largura efetiva.
		sigma = sigma0*exp(-(x*nexemplos*y)/tau);
		//Calcula a distância lateral.
		l2 = 0;
		k1 = (contt+1) % 3;
		if (k1 == 0)
		{
			k1 = 3;
		}
		l1 = 1 + contt/3;
		l2 = pow((k-k1),2) + pow((1-l1),2);
		//calcula a vizinhança topológica.
		h = exp(-l2/(2*sigma*sigma));
		//Calcula a taxa de aprendizagem.
		eta = eta0*exp(-(x*nexemplos + y)/tau);
		//Calcula o ajuste para o peso dos arcos do neurônio.
		for (cont2 = 0; cont2 < nentrada; cont2++)
		{
			w[cont2][contt] = w[cont2][contt] + eta*h*(entradas[cont2][y] - w[cont2][contt]);
		}
	}
	//teste de parada.
	if (deucl < errodes)
	{
		printf("\nFinalizado pelo erro!");
		break;
	}
	}
	printf("\nPesos finais: \n");
	for (contt = 0;contt < nentrada;contt++)
	{
		for (cont2 = 0;cont2 < nneuronio; cont2++)
		{
			printf("w[%d][%d] = %f\n",contt,cont2,w[contt][cont2]);
		}	
	}
	printf("\nTestes de entradas e saídas\n");
	for (cont2 = 0; cont2 < 5;cont2++)
	{
		for (contt = 0; contt<nentrada; contt++)
		{
			if (cont2 < 3)
			{
				teste[contt][cont2] = entradas[contt][cont2];
			}
			if (cont2 == 3)
			{
				teste[contt][cont2] = rand()%20;
			}
			if (cont2 == 4)
			{
				printf("\nDigite 1 entrada: ");
				scanf("%f", &teste[contt][cont2]);
			}
		}
	}
	for (x = 0; x<5;x++)
	{
		for (contt = 0; contt < nneuronio; contt++)
		{
			d[contt] = 0;
			for (cont2 = 0; cont2 < nentrada; cont2++)
			{
				d[contt] = d[contt] + (teste[cont2][x]-w[cont2][contt])*(teste[cont2][x]-w[cont2][contt]);
			}
		}
		printf("\nd = %f\n",d[contt]);	
	}
	//Calcula a menor distância.
	deucl = d[0];
	for (contt=0;contt < nneuronio;contt++)
	{
		if (deucl >= d[contt])
		{
			deucl = d[contt];
		}
		printf("\ndeucl = %f\n",deucl);
	}	
	for (contt = 0; contt < nneuronio; contt++)
	{
		if (deucl == d[contt])
		{
			k = (contt + 1) % 3;
			if (k == 0)
			{
				k = 3;
			}
			l = 1 + contt/3;
			break;
		}
	}
	printf("\nEntradas: \n");
	for (y=0;y<nentrada; y++)
	{
		printf("%f\t",teste[y][x]);
		printf("\nNeurônio ativado: %d (%d %d) \n", contt + l, l, k);
	}
}

