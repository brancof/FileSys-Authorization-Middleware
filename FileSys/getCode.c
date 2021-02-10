#include "getCode.h"


size_t cStringF(void *ptr, size_t size, size_t nmemb, struct campo *s)
{ 
  size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;
  
  return size*nmemb;
}

void iString(struct campo *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

char* realiza_get(char* url)
{
  CURL *curl;
  CURLcode res;

  struct campo json;
  iString(&json);
 
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cStringF);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &json);
 
    res = curl_easy_perform(curl);
    
    if(res != CURLE_OK)
      return strdup("forbidden");
    
    curl_easy_cleanup(curl);
    return strdup(json.ptr);
  }
  return "Error";
}