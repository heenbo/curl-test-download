#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <curl/curl.h>

#define URL "http://o9o6wy2tb.bkt.clouddn.com/a.txt"
#define PATH "./"
#define FILE_NAME "a.txt"

int curl_download_file_from_url(char * url, char * path, char * file_name);

int main(int argc, char * argv[])
{

	curl_download_file_from_url(URL, PATH, FILE_NAME);

	return 0;
}

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
	size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
	return written;
}

int curl_download_file_from_url(char * url, char * path, char * file_name)
{
	CURL *curl_handle;
	FILE *pfile;
	int len = 0;
	char * save_file_path = NULL;

	len = strlen(path) + strlen(file_name);
	save_file_path = malloc(len*sizeof(char));
	if(NULL == save_file_path)
	{
		printf("error save_file_path malloc failure\n");
		return -1;
	}
	strcpy(save_file_path, path);
	strcat(save_file_path, file_name);	
	printf("save_file_path:%s\n", save_file_path);

	curl_global_init(CURL_GLOBAL_ALL);
	/* init the curl session */
	curl_handle = curl_easy_init();
	/* set URL to get here */
	curl_easy_setopt(curl_handle, CURLOPT_URL, url); 
	/* Switch on full protocol/debug output while testing */
	curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
	/* disable progress meter, set to 0L to enable and disable debug output */
	curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
	/* send all data to this function  */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

	/* open the file */
	pfile = fopen(save_file_path, "wb");
	if(pfile) 
	{
		/* write the page body to this file handle */
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pfile);
		/* get it! */
		curl_easy_perform(curl_handle);
		/* close the header file */
		fclose(pfile);
	}

	free(save_file_path);
	/* cleanup curl stuff */
	curl_easy_cleanup(curl_handle);		

	return 0;
}
