#include "spectrum_t1.h"
#include "test_util.h"
#include <math.h>
#include <string.h>

#define IS_NAN(x) ((x) != (x))

static void test_off_token(void)
{
    CHECK(IS_NAN(spectrum_temp_from_token("OFF")));
    CHECK(IS_NAN(spectrum_temp_from_token("off")));
    CHECK(IS_NAN(spectrum_temp_from_token("Off")));
    CHECK(IS_NAN(spectrum_temp_from_token("OFF ")));
    CHECK(IS_NAN(spectrum_temp_from_token(NULL)));
    CHECK(IS_NAN(spectrum_temp_from_token("")));
    CHECK(IS_NAN(spectrum_temp_from_token("xyz")));
}

static void test_numeric_token(void)
{
    CHECK(spectrum_temp_from_token("27.5") == 27.5f);
    CHECK(spectrum_temp_from_token("0") == 0.0f);
    CHECK(spectrum_temp_from_token("85.0") == 85.0f);
    CHECK(spectrum_temp_from_token("-1.5") == -1.5f);
}

static void test_off_prefix_not_offset(void)
{
    /* "OFFSET" не должен считаться OFF; нет цифр → NaN */
    CHECK(IS_NAN(spectrum_temp_from_token("OFFSET")));
}

static void test_json(void)
{
    char b[16];
    CHECK(spectrum_temp_json(b, sizeof b, spectrum_temp_from_token("OFF")) > 0);
    CHECK(strcmp(b, "null") == 0);
    CHECK(spectrum_temp_json(b, sizeof b, 27.5f) > 0);
    CHECK(strcmp(b, "27.5") == 0);
    CHECK(spectrum_temp_json(b, 1, 27.5f) == -1);
}

void t1_settle_suite(void)
{
    test_off_token();
    test_numeric_token();
    test_off_prefix_not_offset();
    test_json();
}
