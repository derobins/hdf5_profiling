/* Test program for profiling the H5Dread() API call */

#include <stdio.h>
#include <stdlib.h>
#include <hdf5.h>
#include <valgrind/callgrind.h>

int main(int argc, char *argv[])
{
    hid_t fid = H5I_INVALID_HID;
    hid_t did = H5I_INVALID_HID;
    uint64_t *data = NULL;
    herr_t err;

    if (argc != 2) {
        fprintf(stderr, "Please specify the file name on the command line.\n");
        return EXIT_FAILURE;
    }

    if ((fid = H5Fopen(argv[1], H5F_ACC_RDONLY, H5P_DEFAULT)) < 0)
        goto badness;

    if ((did = H5Dopen2(fid, "test", H5P_DEFAULT)) < 0)
        goto badness;

    if ((data = calloc(100, sizeof(uint64_t))) == NULL)
        goto badness;

    CALLGRIND_START_INSTRUMENTATION;
    err = H5Dread(did, H5T_STD_I64LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
    CALLGRIND_STOP_INSTRUMENTATION;

    if (err < 0)
        goto badness;

    if (H5Fclose(fid) < 0)
        goto badness;
    if (H5Dclose(did) < 0)
        goto badness;

    return EXIT_SUCCESS;

badness:

    fprintf(stderr, "BADNESS\n");

    H5E_BEGIN_TRY {
        H5Fclose(fid);
        H5Dclose(did);
    } H5E_END_TRY;

    return EXIT_FAILURE;
}
