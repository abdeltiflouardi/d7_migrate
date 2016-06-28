<?php

/**
 * @file
 * Declares our migrations.
 */
    

/**
 * Implements hook_migrate_api().
 */
function migrate_os_migrate_api() {
  $api = array(
    'api' => 2,
    'groups' => array(
      'os' => array(
        'title' => t('Os Migrations'),
      ),
    ),

    'migrations' => array(
      'ServiceTerm' => array(
         'class_name' => 'ServiceTermMigration',
         'group_name' => 'os',
      ),
      'CategoryTerm' => array(
         'class_name' => 'CategoryTermMigration',
         'group_name' => 'os',
      ),
      'OsNode' => array(
         'class_name' => 'OsNodeMigration',
         'group_name' => 'os',
         'dependencies' => array(
           'CategoryTerm',
           'ServiceTerm',
         ),
      ),
    ),
  );
  return $api;
}

