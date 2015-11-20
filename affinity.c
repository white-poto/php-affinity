/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_affinity.h"

#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/sysinfo.h>
#include<unistd.h>

#define __USE_GNU
#include<sched.h>
#include<ctype.h>
#include<string.h>

/* If you declare any globals in php_affinity.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(affinity)
*/

/* True global resources - no need for thread safety here */
static int le_affinity;

/* {{{ affinity_functions[]
 *
 * Every user visible function must have an entry in affinity_functions[].
 */
const zend_function_entry affinity_functions[] = {
	PHP_FE(confirm_affinity_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(setaffinity,	NULL)		/* For testing, remove later. */
	PHP_FE(getaffinity,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in affinity_functions[] */
};
/* }}} */

/* {{{ affinity_module_entry
 */
zend_module_entry affinity_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"affinity",
	affinity_functions,
	PHP_MINIT(affinity),
	PHP_MSHUTDOWN(affinity),
	PHP_RINIT(affinity),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(affinity),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(affinity),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_AFFINITY_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_AFFINITY
ZEND_GET_MODULE(affinity)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("affinity.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_affinity_globals, affinity_globals)
    STD_PHP_INI_ENTRY("affinity.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_affinity_globals, affinity_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_affinity_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_affinity_init_globals(zend_affinity_globals *affinity_globals)
{
	affinity_globals->global_value = 0;
	affinity_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(affinity)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(affinity)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(affinity)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(affinity)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(affinity)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "affinity support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

PHP_FUNCTION(setaffinity)
{
	long cpu_id = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &cpu_id) == FAILURE) {
        RETURN_NULL();
    }

	int num = sysconf(_SC_NPROCESSORS_CONF);
	if(cpu_id > num){
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "cpu_id more than the total number of CPU");
		RETURN_FALSE;
	}

	cpu_set_t mask;
	CPU_ZERO(&mask);
    CPU_SET(cpu_id, &mask);

	if(sched_setaffinity(0, sizeof(mask), &mask) == -1){
		RETURN_FALSE;
	}

	RETURN_TRUE;
}

PHP_FUNCTION(getaffinity)
{
	int num = sysconf(_SC_NPROCESSORS_CONF);
	cpu_set_t get;
	CPU_ZERO(&get);

	if(sched_getaffinity(0, sizeof(get), &get) == -1){
		RETURN_FALSE;
	}
	int i;
	for(i=0; i<num; i++){
		if(CPU_ISSET(i, &get)){
			RETURN_LONG(i);
		}
	}

	RETURN_FALSE;
}



/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_affinity_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_affinity_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "affinity", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
