#pragma once

#include "resource.h"
#include<stdlib.h>
#include<stdlib.h>

HINSTANCE hInst;

struct Nod{

	double score;
	int *uz;
	int *sol;
	int next_nod;
	int real_score;
	int incarcatura;
};

Nod sol;

struct obiect{
	int id;
	int valoare;
	int greutate;
	WCHAR nume[20];
};

struct coada {
	coada *next;
	Nod *node;
};

obiect *v, *h;
obiect ob;

int nrObiecte, capacitate;

//coada cu prioritate pun elementul in coada in ordine descrescatoare a scorului(valorii)
void push(coada **prim, coada **ultim, Nod *q)
{
	coada *w, *c, *b = 0;
	w = (coada*)malloc(sizeof(coada));

	w->node = q;
	if (*prim == 0)
	{
		w->next = 0;
		(*prim) = w;
		*ultim = w;
	}
	else
	{
		c = *prim;
		while (c)
		{
			if (w->node->score > c->node->score)break;
			b = c;
			c = c->next;
		}

		if (b == 0)
		{
			w->next = (*prim);
			*prim = w;
		}
		else
		{
			w->next = b->next;
			b->next = w;
			if (b == *ultim)
				*ultim = w;
		}
	}
}

Nod* top(coada **prim, coada **ultim){

	return (*prim)->node;
}

void pop(coada **prim, coada **ultim) 
{
	coada *c;
	if ((*prim) != 0)
	{
		c = *prim;
		(*prim) = (*prim)->next;
		free(c);
		if (*prim == 0) *ultim = 0;
	}
}





Nod * f(obiect v[], int n, int uz[], int capacitate)
{
	int suma = 0, real_score = 0;
	int next, ok = 1;
	double scor = 0;

	Nod *q = (Nod*)malloc(sizeof(Nod));
	q->uz = (int *)calloc(n, sizeof(int));
	q->sol = (int*)calloc(n, sizeof(int));

	q->next_nod = -1;

	for (int i = 0; i<n; ++i)
		if (uz[i] == 1)
		{
		suma += v[i].greutate;
		scor += v[i].valoare;
		q->uz[i] = 1;
		q->sol[v[i].id] = 1;

		}
		else
			if (uz[i] == -1)q->uz[i] = -1;
	real_score = scor;
	q->incarcatura = suma;

	for (int i = 0; i<n && ok; ++i)
	{
		if (uz[i] == 0)
		{
			if (suma + v[i].greutate <= capacitate)
			{
				suma += v[i].greutate;
				scor += v[i].valoare;
				real_score = scor;
				q->sol[v[i].id] = 1;
			}
			else {
				scor += (capacitate - suma)*v[i].valoare / v[i].greutate;
				q->next_nod = i;
				ok = 0;
			}
		}
		q->score = scor;
		q->real_score = real_score;
	}
	return q;
}

// Message handler for about box.
INT_PTR CALLBACK Procedura(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		WCHAR buff[100];
		WCHAR minibuff[20];
		int pr_max = 0;
		for (int i = 0; i < nrObiecte; i++)
			if (sol.sol[i] == 1)
			{
			SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, NULL, (LPARAM)h[i].nume);
			pr_max += h[i].valoare;
			}
		//wchar_t val[10]; _itow_s(pr_max,val,10);
		SetDlgItemInt(hDlg, IDC_EDIT1, pr_max, NULL);
	}
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


void ordonare(obiect *v, int n)
{
	obiect aux;
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if ((float)((v)[i].valoare / (v)[i].greutate) < (float)((v)[j].valoare / (v)[i].greutate))
			{
		aux = v[i];
		v[i] = v[j];
		v[j] = aux;
			}

}


void solve(obiect v[], obiect *h, int n, int capacitate)
{
	ordonare(v, n);

	int *uz = (int*)calloc(n, sizeof(int));
	int max_score = 0;
	Nod *q = f(v, n, uz, capacitate);
	Nod p;
	coada *prim, *ultim;
	prim = ultim = 0;

	push(&prim, &ultim, q);
	while (prim)
	{
		p = *top(&prim, &ultim);
		pop(&prim, &ultim);
		if (p.score >= max_score){

			if (p.next_nod == -1){ //daca e sol

				max_score = p.real_score;
				// message box      printf("max_score= %d\n", max_score);
				sol = p;
			}
			else{

				if (capacitate - p.incarcatura >= v[p.next_nod].greutate)
				{
					p.uz[p.next_nod] = 1;
					q = f(v, n, p.uz, capacitate);
					push(&prim, &ultim, q);
				}
				p.uz[p.next_nod] = -1;
				q = f(v, n, p.uz, capacitate);
				push(&prim, &ultim, q);
			}

		}


	}
	int nr = 0;
	for (int i = 0; i < n; i++)
		if (p.uz[i] != -1)
		{
		nr++;
		break;
		}
	if (nr){
		DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), (NULL), Procedura);
	}
	else
		MessageBox(NULL, L"Nu exista solutie!", L"Info", MB_ICONINFORMATION);

}

