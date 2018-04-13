Typography magic
================

Brings a set of typographical automatic enhancement for user-inputed text
using the following libraries:

- https://github.com/heiglandreas/Org_Heigl_Hyphenator
- https://github.com/jolicode/JoliTypo
- https://github.com/makinacorpus/php-header-fixer

It provides the following integration:

- higly configurable field formatter that extends core's text module one,
  providing all the semantic, typographic, and micro-typographic features,
- independent filters implementations for semantic and micro-typographic
  features
- page and node templates processing to fix titles micro typography.

It will, in the future, bring the following additional features:

- twig filters when in use with makinacorpus/drupal-sf-dic,
- block template processing for titles,
- and probably a set of other features.

Why the name ? Because the "typography" namespace on https://www.drupal.org
gives a 403 error so I guess it cannot be use.

This module replaces the https://github.com/Anaethelion/JoliTypo-for-Drupal
Drupal module (which works gracefully, we personnally know its author).

Installation
============

For starters, you should install this module using composer in order for all
dependencies to be fetched:

.. code-block:: sh

   composer require makinacorpus/drupal-typomagic

Then enable it:

.. code-block:: sh

   drush -y en typomagic

Getting started
===============

Configure your filters or field formatters as usual, forms will drive you.

Per default, the JoliTypo filter is configured for french typography, in order
to use it for another language, please refer to its documentation located at
https://github.com/jolicode/JoliTypo#fixer-recommendations-by-locale

Configuration
=============

Not every bit of the configuration will be documented here, as the configuration
options are numerous and may evolve in the future, anyhow, here is a few
variables you may want to tweak in your ``settings.php`` file:

.. code-block:: php

   $conf['typomagic_title_page'] = false

Will disable page title processing.

.. code-block:: php

   $conf['typomagic_title_node'] = false

Will disable node title processing.
