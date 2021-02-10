#include "email.h"

 
char * from = "<gestaoFlorestalPortugal@gmail.com>";

static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
  struct upload_status *upload_ctx = (struct upload_status *)userp;

  size_t b_copy = upload_ctx->sizl < size*nmemb ? upload_ctx->sizl : size*nmemb;
  b_copy = upload_ctx->sizl < 10 ? upload_ctx->sizl : 10;

  if(size*nmemb < 1)
    return 0;

  if(upload_ctx->sizl)
  {
    memcpy((char*)ptr, (char*)upload_ctx->rptr, b_copy);
    upload_ctx->rptr+=b_copy;
    upload_ctx->sizl-=b_copy;
    return b_copy;
  }

  return 0;
}

int enviar_email(const char* destino, const char* username, const char* codigo, const char* filename)
{
    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = NULL;
    struct upload_status upload_ctx;

    curl = curl_easy_init();
    if(curl)
    {
        // This is what our message will look like, but with details filled in.
        const char payload_template[] =
        "To: %s\r\n"
        "From: %s\r\n"
        "Content-Type: text/html; charset=us-ascii\r\n"
        "Subject: [Fuse] - Auth Permition\r\n"
        "<html><body>\r\n"
        "<h3>Acesso pedido por user: <u>%s</u></h3>\r\n"
        "<h3>Path: <u>%s</u></h3>\r\n\r\n"
        "<h3>Aceda ao seguinte link se quiser ceder permissoes: <p>%s%s</p></h3> \r\n"
        "<h3>Ou entao insira o seguinte codigo: <u>%s</u> em %s </h3> \r\n"
        "</body></html>\r\n\r\n";

        size_t payloadLen = strlen(payload_template) +  
                                  strlen(destino) + strlen(from) +
                                  strlen(filename) + strlen(username) + strlen(WEB_SERVER) +
                                  strlen(codigo) + strlen(codigo) + strlen(WEB_SERVER) + 1;

        char* payload_text = malloc(payloadLen);

        memset(payload_text, 0, payloadLen);

        sprintf(payload_text, payload_template, destino, from, username, filename, WEB_SERVER, codigo, codigo, WEB_SERVER);

        upload_ctx.rptr = payload_text;
        upload_ctx.sizl = (long)strlen(payload_text);
 
    curl_easy_setopt(curl, CURLOPT_USERNAME, "gestaoFlorestalPortugal@gmail.com");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "gestaoFlorestal2020");
 
    curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");
 
    curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
 
    curl_easy_setopt(curl, CURLOPT_CAINFO, SSL_CERT);
 
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, from);
 
    recipients = curl_slist_append(recipients, destino);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
 
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
    curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
 
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
 
    res = curl_easy_perform(curl);
 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
 
    curl_slist_free_all(recipients);
 
    curl_easy_cleanup(curl);
  }
 
  return (int)res;
}
