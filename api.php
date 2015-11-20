<?php
/**
 * @author Jenner <hypxm@qq.com>
 * @blog http://www.huyanping.cn
 * @license https://opensource.org/licenses/MIT MIT
 * @datetime: 2015/11/20 12:11
 */

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