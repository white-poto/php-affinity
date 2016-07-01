php-affinity
==================
A PHP extension which provides functions to modify CPU affinity

Introduce
------------------
Affinity extension provides three functions:
+ getaffinity get CPU number which current process is running in.
+ setaffinity change the process to another CPU
+ getcpucores get number of CPU cores

simple-fork-php framework
-------------------------
This is [](http://example.com/ "Title") inline link.
[simple-fork-php](https://github.com/huyanping/simple-fork-php "simple-fork-php") 
is A multi-processes management framework. 
Its interfaces are like `Thread` and `Runnable` in java.
It is useful for someone who wants to write multi-processes programs.

Install
---------------------
```shell
wget https://github.com/huyanping/php-affinity/archive/0.1.tar.gz
tar zxvf 0.1.tar.gz
cd affinity
phpize
./configure --with-php-config=/path/to/php-config
make && make test && make install
```

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