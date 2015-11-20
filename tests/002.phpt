--TEST--
Check for affinity presence
--SKIPIF--
<?php if (!extension_loaded("affinity")) print "skip"; ?>
--FILE--
<?php
if(setaffinity(0)){
    echo "set success" . PHP_EOL;
}
if(getaffinity()){
    echo "get success" . PHP_EOL;
}
?>
--EXPECT--
set success
get success
