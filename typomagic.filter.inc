<?php
/**
 * Filter API integration.
 */

/**
 * Implements hook_filter_info().
 */
function typomagic_filter_info() {
  return [
    'typomagic_header' => [
      'title'             => t('Fixes header semantical hierarchy'),
      'process callback'  => '_typomagic_filter_header',
      'settings callback' => '_typomagic_filter_header_settings',
      'weight'            => 100,
      'default settings'  => typomagic_defaults_header(),
    ],
    'typomagic_jolittypo' => [
      'title'             => t('Fixes language-centric typography and hyphenation'),
      'process callback'  => '_typomagic_filter_jolitypo',
      'settings callback' => '_typomagic_filter_jolitypo_settings',
      'weight'            => 101,
      'default settings'  => typomagic_defaults_jolitypo(),
    ],
  ];
}

/**
 * Implements callback_filter_settings().
 */
function _typomagic_filter_header_settings($form, &$form_state, $filter, $format, $defaults) {
  return typomagic_form_header($filter->settings ?? []);
}

/**
 * Implements callback_filter_process().
 */
function _typomagic_filter_header($text, $filter) {
  return typomagic_run_header($text, $filter->settings ?? []);
}

/**
 * Implements callback_filter_settings().
 */
function _typomagic_filter_jolitypo_settings($form, &$form_state, $filter, $format, $defaults) {
  return typomagic_form_jolitypo($filter->settings ?? []);
}

/**
 * Implements callback_filter_process().
 */
function _typomagic_filter_jolitypo($text, $filter) {
  return typomagic_run_jolitypo($text, $filter->settings ?? []);
}
