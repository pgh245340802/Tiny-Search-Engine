/* pageio.c --- 
1;95;0c1;95;0c1;95;0c * 
 * 
 * Author: Guanghan Pan
 * Created: Thu Oct 17 19:35:35 2019 (-0400)
 * Version: 
 * 
 * Description: 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <unistd.h>
#include <webpage.h>
#include <pageio.h>

int32_t pagesave(webpage_t *pagep, int id, char *dirnm){
	FILE *fp;
	char filename[20];
	// create file name using dirname
	sprintf(filename,"%s%d",dirnm,id);
	// open the file and write the contents
	fp = fopen(filename,"w");
	fprintf(fp,"%s\n%d\n%d\n%s",webpage_getURL(pagep),webpage_getDepth(pagep)
					,webpage_getHTMLlen(pagep), webpage_getHTML(pagep));
	fclose(fp);
	return 0;
}

webpage_t *pageload(int id, char *dirnm){
	FILE *fp;
	char filename[20];

	sprintf(filename,"%s%d",dirnm,id);
	if((fp = fopen(filename,"r"))==NULL)
		return NULL;
	else {
		char url[50],depth[5],lines[5],html[100],html_init[50000] = "";
		fscanf(fp,"%s\n%s\n%s\n",url,depth,lines);
		int depth_int = atoi(depth);
		while (fgets(html,100,fp) != NULL)
			strcat(html_init,html);
		webpage_t *web = webpage_new(url,depth_int,html_init);
		
		return web;
	}
		
}