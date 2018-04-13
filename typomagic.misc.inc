<?php
/**
 * Various Drupal subsystem integration.
 *
 * @todo
 *   bloc titles
 */

/**
 * Implements hook_process_HOOK().
 */
function typomagic_process_page(&$variables) {
  if (variable_get('typomagic_title_page', true)) {
    $variables['title'] = typomagic_run_jolitypo($variables['title']);
  }
}

/**
 * Implements hook_process_HOOK().
 */
function typomagic_process_node(&$variables) {
  if (variable_get('typomagic_title_node', true)) {
    $variables['title'] = typomagic_run_jolitypo($variables['title']);
  }
}
