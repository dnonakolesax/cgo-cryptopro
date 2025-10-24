#include <gtest/gtest.h>
#include <cstdint> 

#define CONTAINER_NAME "\\\\.\\HDIMAGE\\de47006e0-87a9-36a2-dfd7-5c65af93896"
#define CONTAINER_PASSWORD "notsosampletext2003"
#define CERT_FINGERPRINT "771335c15361bf009760896784375059789ab2bb"

#define ERROR_WRONG_PASS 0x8010006B
#define ERROR_CONT_DOESNT_EXIST 0x80090016

extern "C" {
    #include "cryptopro.h"
}

TEST(acquire_context, acquire_context) {
    struct provider {
        unsigned int provider;
    };
    provider* prov = (provider*)malloc(sizeof(provider));

    uint code = acquire_provider((void*)CONTAINER_NAME, (void*)CONTAINER_PASSWORD, (void*)(prov));
    ASSERT_EQ(code, 0);
    release_provider((void*)(prov));
}

TEST(acquire_context_wrong_pass, acquire_context_wrong_pass) {
    struct provider {
        unsigned int provider;
    };
    provider* prov = (provider*)malloc(sizeof(provider));

    uint code = acquire_provider((void*)CONTAINER_NAME, (void*)"lmaoxd", (void*)(prov));
    ASSERT_EQ(code, ERROR_WRONG_PASS);
}

TEST(acquire_context_wrong_contname, acquire_context_wrong_contname) {
    struct provider {
        unsigned int provider;
    };
    provider* prov = (provider*)malloc(sizeof(provider));

    uint code = acquire_provider((void*)"\\\\.\\HDIMAGE\\000000000-0000-0000-0000-00000000000", (void*)CONTAINER_PASSWORD, (void*)(prov));
    ASSERT_EQ(code, ERROR_CONT_DOESNT_EXIST);
}

TEST(sign, sign) {
    struct provider {
        uintptr_t provider;
    };
    provider* prov = (provider*)malloc(sizeof(provider));

    uint code = acquire_provider((void*)CONTAINER_NAME, (void*)CONTAINER_PASSWORD, (void*)(prov));
    ASSERT_EQ(code, 0);

    struct Result {
        unsigned char* signature;
    };
    Result* sig = (Result*)malloc(sizeof(Result));

    uint scode = sign((void*)(prov->provider), (void*)"testmessage", (void*)(sig));
    ASSERT_EQ(scode, 0);

    release_provider((void*)(prov));
}
