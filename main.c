#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <audio_route/audio_route.h>

#define MIXER_XML_PATH "/system/etc/mixer_paths.xml"
#define DEFAULT_MIXER_CARD 0

struct audio_route *ar = NULL;

void print_usage(__attribute__((unused)) int argc, char * const argv[])
{
	printf("Usage: %s mixer_paths.xml [route]\n", argv[0]);
}

int main(int argc, char * const argv[])
{
	int opt;
	const char* xml_path = MIXER_XML_PATH;
	const char* path;
	int card = DEFAULT_MIXER_CARD;
	int i;

	while ((opt = getopt(argc, argv, "df")) != -1) {
		printf("parsing %c, optind %d\n", opt, optind);
	    switch (opt) {
	    case 'd':
	    	card = atoi(argv[optind]);
    		optind++;
	    	break;
    	case 'f':
    		xml_path = argv[optind];
    		optind++;
	    	break;
	    default:
	        fprintf(stderr, "Usage: %s [-d] [file...]\n", argv[0]);
	        exit(EXIT_FAILURE);
	    }
	}

	if (argc < 2) {
		print_usage(argc, argv);
		return -1;
	}

	printf("Using device %d\n", card);
	printf("Using mixer_path.xml: %s\n", xml_path);

	ar = audio_route_init(card, xml_path);
	if (ar == NULL) {
		fprintf(stderr, "audio_route_init error. %s\n", strerror(errno));
		return -1;
	}

	/*
	 Don't want to reset because the reset values taken as the settings
	 that were saved when audio_route is initialized.
	 This is supposed to be the default values of the sound card when
	 the Android audio HAL is started at boot.
	 */
	// printf("audio_route_reset\n");
	// audio_route_reset(ar);

	for (i = optind; i < argc; i++) {
		path = argv[i];
		printf("audio_route_apply_path(path=%s)\n", path);
		audio_route_apply_path(ar, path);
	}

	printf("audio_route_update_mixer\n");
	audio_route_update_mixer(ar);

	printf("audio_route_free\n");
	audio_route_free(ar);


	return EXIT_SUCCESS;
}