php-affinity
==================
php extension which provide functions to modify CPU affinity

Introduce
------------------
affinity provides three functions:
+ getaffinity get CPU number which current process is running in.
+ setaffinity change the process to another CPU
+ getcpucores get number of CPU cores

Install
---------------------
tar zxvf affinity.tar.gz
cd affinity
phpize
./configure --with-php-config=/path/to/php-config
make && make test && make install

API
---------------------
```php
/**
 * set CPU affinity
 *
 * @param $cpu_id
 * @return bool
 */
function setaffinity($cpu_id){
    $num = getcpucores();
    if($cpu_id >= $num){
        return false;
    }
    $set = system_call($cpu_id);
    if($set === -1){
        return false;
    }

    return true;
}

/**
 * get CPU affinity
 *
 * @return bool
 */
function getaffinity(){
    $cpu_id = system_call();
    if($cpu_id === -1){
        return false;
    }
    return $cpu_id;
}


/**
 * get number of CPU
 *
 * @return bool
 */
function getcpucores(){
    $nums = system_call();
    if($nums === -1){
        return false;
    }
    return $nums;
}
```