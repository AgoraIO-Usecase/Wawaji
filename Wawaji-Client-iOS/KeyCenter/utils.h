#pragma once

#include <string>
#include <sstream>
//#include <openssl/hmac.h>
#include <stdexcept>
#include <iomanip>
#include <cstddef>

#include <CommonCrypto/CommonDigest.h>
#include <CommonCrypto/CommonHMAC.h>

namespace agora { namespace tools {
    const uint32_t HMAC_LENGTH = 20;
    const uint32_t SIGNATURE_LENGTH = 40;
    const uint32_t APP_ID_LENGTH = 32;
    const uint32_t UNIX_TS_LENGTH = 10;
    const uint32_t RANDOM_INT_LENGTH = 8;
    const uint32_t UID_LENGTH = 10;
    const uint32_t VERSION_LENGTH = 3;
    const std::string  RECORDING_SERVICE = "ARS"; 
    const std::string  PUBLIC_SHARING_SERVICE = "APSS"; 
    const std::string  MEDIA_CHANNEL_SERVICE = "ACS";

    template <class T>
        class singleton
        {
            public:
                static T* instance()
                {
                    static T inst;
                    return &inst;
                }
            protected:
                singleton(){}
                virtual ~singleton(){}
            private:
                singleton(const singleton&);
                singleton& operator = (const singleton& rhs);
        };

    class crypto : public singleton<crypto>
    {
        public:
            // HMAC
            std::string hmac_sign(const std::string& message)
            {
                return hmac_sign2(hmac_key_, message, 20);
            }

            std::string hmac_sign2(const std::string& appCertificate, const std::string& message, uint32_t signSize)
            {
                if (appCertificate.empty()) {
                    /*throw std::runtime_error("empty hmac key");*/
                    return "";
                }
                
                char cHMAC[signSize];
                CCHmac(kCCHmacAlgSHA1, appCertificate.data(), appCertificate.size(), message.data(), message.size(), cHMAC);
                return std::string(cHMAC, signSize);

//                
//                return std::string((char *)HMAC(EVP_sha1()
//                            , (const unsigned char*)appCertificate.data()
//                            , appCertificate.length()
//                            , (const unsigned char*)message.data()
//                            , message.length(), NULL, NULL)
//                        , signSize);
            }

            bool hmac_verify(const std::string & message, const std::string & signature)
            {
                return signature == hmac_sign(message);
            }
        private:
            std::string hmac_key_;
    };


    inline std::string stringToHex(const std::string& in)
    {
        static const char hexTable[]= "0123456789abcdef";

        if (in.empty()) {
            return std::string();
        }
        std::string out(in.size()*2, '\0');
        for (uint32_t i = 0; i < in.size(); ++i){
            out[i*2 + 0] = hexTable[(in[i] >> 4) & 0x0F];
            out[i*2 + 1] = hexTable[(in[i]     ) & 0x0F];
        }
        return out;
    }
 
}}
