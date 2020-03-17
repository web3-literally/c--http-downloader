// downtest.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "downtest.h"

#include <tchar.h>
#include <curl/curl.h>

// This is an example of an exported variable
DOWNTEST_API int ndowntest=0;

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}

// This is an example of an exported function.
extern "C" DOWNTEST_API int fndown(void)
{
	CURL *curl;
	FILE *fp;
	CURLcode res;
	auto url = "http://localhost/temp/BotInstaller_1.0.1.zip";
	TCHAR outfilename[FILENAME_MAX] = TEXT("temp.zip");
	curl = curl_easy_init();
	if (curl) {
		errno_t err = _tfopen_s(&fp, outfilename, TEXT("wb"));

		if (err) {
			_tprintf(TEXT("temp.zip open failed\n"));
			return -1;
		}

		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		res = curl_easy_perform(curl);
		/* always cleanup */
		curl_easy_cleanup(curl);

		err = fclose(fp);
		_tprintf(TEXT("download finished"));
		if (err) {
			_tprintf(TEXT("temp.zip close failed\n"));
			return -1;
		}
	}
	return 0;
}
