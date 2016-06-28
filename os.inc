<?php

class ServiceTermMigration extends Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Import services taxonomy from CSV file.');

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'tid' => array('type' => 'int',
                          'unsigned' => TRUE,
                          'not null' => TRUE,
                          'description' => t('Source ID'),
                         )
        ),
        MigrateDestinationTerm::getKeySchema()
      );

    // Create a MigrateSource object, which manages retrieving the input data.
    $path = dirname(__FILE__) . '/';
    $this->source = new MigrateSourceCSV($path . 'services.csv', $this->csvcolumns());

    $this->destination = new MigrateDestinationTerm('services');

    $this->addFieldMapping('name', 'source_name');
  }

  protected function csvcolumns() {
    // Note: Remember to subtract 1 from column number at http://www.retrosheet.org/gamelogs/glfields.txt
    $columns[0] = array('tid', 'Term ID');
    $columns[1] = array('source_name', 'Name');

    return $columns;
  }
}

class CategoryTermMigration extends Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Import categories from CSV file.');

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'tid' => array('type' => 'int',
                          'unsigned' => TRUE,
                          'not null' => TRUE,
                          'description' => t('Source ID'),
                         )
        ),
        MigrateDestinationTerm::getKeySchema()
      );

    // Create a MigrateSource object, which manages retrieving the input data.
    $path = dirname(__FILE__) . '/';
    $this->source = new MigrateSourceCSV($path . 'categories.csv', $this->csvcolumns(), array('delimiter' => ';'));

    $this->destination = new MigrateDestinationTerm('categories');

    $this->addFieldMapping('name', 'source_name');
    $this->addFieldMapping('field_icon', 'icon');
  }

  protected function csvcolumns() {
    // Note: Remember to subtract 1 from column number at http://www.retrosheet.org/gamelogs/glfields.txt
    $columns[0] = array('tid', 'Term ID');
    $columns[1] = array('source_name', 'Name');
    $columns[2] = array('icon', 'Icon');

    return $columns;
  }
}

class OsNodeMigration extends Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Import os list from CSV file.');

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'nid' => array('type' => 'int',
                          'unsigned' => TRUE,
                          'not null' => TRUE,
                          'description' => t('Source ID'),
                         )
        ),
        MigrateDestinationNode::getKeySchema()
      );

    // Create a MigrateSource object, which manages retrieving the input data.
    $path = dirname(__FILE__) . '/';
    $this->source = new MigrateSourceCSV($path . 'os.csv', $this->csvcolumns());

    $this->destination = new MigrateDestinationNode('os');

    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('field_lastname', 'lastname');
    $this->addFieldMapping('field_firstname', 'firstname');

    $this->addFieldMapping('field_services', 'services')
        ->separator(',');

    $this->addFieldMapping('field_categories', 'categories')
         ->separator('|');
  }

  protected function csvcolumns() {
    // Note: Remember to subtract 1 from column number at http://www.retrosheet.org/gamelogs/glfields.txt
    $columns[0] = array('nid', 'Node ID');
    $columns[1] = array('title', 'Title');
    $columns[2] = array('lastname', 'Lastname');
    $columns[3] = array('firstname', 'Firstname');
    $columns[4] = array('services', 'Services');
    $columns[5] = array('categories', 'Categories');

    return $columns;
  }
}
