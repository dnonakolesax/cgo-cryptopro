#include "cryptopro.h"

unsigned int acquire_provider(void *container, void *password, void *provider) {
    struct provider {
        unsigned int provider;
    };
    HCRYPTPROV hProv = 0;
    if (!CryptAcquireContext(
            &hProv,
            (char*)container,
            NULL,
            PROV_GOST_2012_256,
            CRYPT_SILENT
    )) {
            return GetLastError();
    }
    if (!CryptSetProvParam(
        hProv,
        PP_SIGNATURE_PIN,
        (char*)password,
        0
    )) {
        CryptReleaseContext(hProv, 0);
        return GetLastError();
    }

    //printf("\n%u\n", hProv);
    ((struct provider*)provider)->provider = hProv;
    return 0;
}

unsigned int sign(void *provider, void *payload, void *result) {
    struct Result {
        unsigned char* signature;
    };

    BYTE *pbBuffer = (BYTE *)(payload);
    DWORD dwBufferLen = (DWORD)(sizeof(payload));
    BYTE *pbSignature = NULL;
    HCRYPTHASH hHash = 0;

    //printf("\n%u\n", (HCRYPTPROV)provider);
    if (!CryptCreateHash(
            (HCRYPTPROV)provider,
            CALG_GR3411_2012_256,
            0,
            0,
            &hHash)) {
        return GetLastError();
    }

    if (!CryptHashData(
            hHash,
            pbBuffer,
            dwBufferLen,
            0)) {
        CryptDestroyHash(hHash);
        return GetLastError();
    }

    DWORD dwSigLen = 64;
    unsigned char* signature = (unsigned char*)malloc(dwSigLen);

    if (!CryptSignHash(
            hHash,
            AT_KEYEXCHANGE,
            NULL,
            0,
            signature,
            &dwSigLen)) {
        CryptDestroyHash(hHash);
        return GetLastError();
    }

    // for (int i = 0; i < dwSigLen; i++) {
    //    printf("%02x", signature[i]);
    // }

    ((struct Result*)result)->signature = signature;
    CryptDestroyHash(hHash);

    return 0;
}

void release_provider(void *container) {
    CryptReleaseContext((HCRYPTPROV)container, 0);
}
