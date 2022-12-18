long long binpow(long long a, long long b, long long m) 
{
	a %= m;
	long long res = 1;
	while (b > 0) {
		if (b & 1)
			res = res * a % m;
		a = a * a % m;
		b >>= 1;
	}
	return res;
}

void decifra(int N, int d, int L, int* messaggio, char* plaintext) 
{
    for(int i=0; i<L; i++)
	{
		plaintext[i] = binpow(messaggio[i], d, N);
	}
	plaintext[L]='\0';
}
