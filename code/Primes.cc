typedef unsigned long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;

ll _sieve_size;
bitset<10000010> bs;
vll primes;

void sieve(ll upper) {
    _sieve_size = upper + 1;
    bs.set(); // set all to one
    bs[0] = bs[1] = 0;
    for(ll i = 2; i < _sieve_size; i++) if (bs[i]) {
            for(ll j = i*i; j < _sieve_size; j+= i) {
                bs[j] = 0;
            }
            primes.push_back((int) i);
        }
}

bool isPrime(ll n) {
    if (n <= _sieve_size) return bs[n];
    for(int i = 0; i < (int) primes.size(); i++) {
        if (n % primes[i] == 0) return false;
        if (primes[i] * primes[i] > n) return true;
    }
    return true;
}

bool isPrime_slow(ll n) {
    if(n < 2) return false;
    if(n == 2 || n == 3) return true;
    if(n % 2 == 0 || n % 3 == 0) return false;
    int limit = sqrt(n);
    for(int i = 5; i <= limit; i += 6) {
        if(n % i == 0 || n % (i+2) == 0)
            return false;
    }
    return true;
}


vi primeFactors(ll N) {
    vi factors;
    ll PF_index = 0; ll PF = primes[PF_index];
    while(PF*PF <= N) {
        while(N%PF == 0) {
            N /= PF; factors.push_back(PF);
        }
        PF = primes[++PF_index];
    }
    if(N != 1) factors.push_back(N);
    return factors;
}


// Primes less than 1000:
//      2     3     5     7    11    13    17    19    23    29    31    37
//     41    43    47    53    59    61    67    71    73    79    83    89
//     97   101   103   107   109   113   127   131   137   139   149   151
//    157   163   167   173   179   181   191   193   197   199   211   223
//    227   229   233   239   241   251   257   263   269   271   277   281
//    283   293   307   311   313   317   331   337   347   349   353   359
//    367   373   379   383   389   397   401   409   419   421   431   433
//    439   443   449   457   461   463   467   479   487   491   499   503
//    509   521   523   541   547   557   563   569   571   577   587   593
//    599   601   607   613   617   619   631   641   643   647   653   659
//    661   673   677   683   691   701   709   719   727   733   739   743
//    751   757   761   769   773   787   797   809   811   821   823   827
//    829   839   853   857   859   863   877   881   883   887   907   911
//    919   929   937   941   947   953   967   971   977   983   991   997

// Other primes: largest prime smaller than X is Y
//    10 is 7.
//    100 is 97.
//    1000 is 997.
//    10000 is 9973.
//    100000 is 99991.
//    1000000 is 999983.
//    10000000 is 9999991.
//    100000000 is 99999989.
//    1000000000 is 999999937.
//    10000000000 is 9999999967.
//    100000000000 is 99999999977.
//    1000000000000 is 999999999989.
//    10000000000000 is 9999999999971.
//    100000000000000 is 99999999999973.
//    1000000000000000 is 999999999999989.
//    10000000000000000 is 9999999999999937.
//    100000000000000000 is 99999999999999997.
//    1000000000000000000 is 999999999999999989.
