--TEST--
Check for affinity presence
--SKIPIF--
<?php if (!extension_loaded("affinity")) print "skip"; ?>
--FILE--
<?php
if(setaffinity(0)){
    echo "set success" . PHP_EOL;
}
if(getaffinity() === 0){
    echo "get success" . PHP_EOL;
}
$cpu_cores = intval(shell_exec("cat /proc/cpuinfo | grep processor | wc -l"));
if(getcpucores() == $cpu_cores){
    echo "getcpucores success" . PHP_EOL;
}
?>
--EXPECT--
set success
get success
getcpucores success
