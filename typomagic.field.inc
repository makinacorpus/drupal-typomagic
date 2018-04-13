<?php
/**
 * Field API integration.
 */

/**
 * Implements hook_field_formatter_info().
 */
function typomagic_field_formatter_info() {
  return [
    'typomagic_default' => [
      'label'       => t("Default with typo fixes"),
      'field types' => ['text', 'text_long', 'text_with_summary'],
    ],
    'typomagic_trimmed' => [
      'label'       => t("Trimmed with typo fixes"),
      'field types' => ['text', 'text_long', 'text_with_summary'],
      'settings'    => typomagic_defaults() + ['trim_length' => 600],
    ],
    'typomagic_summary_or_trimmed' => [
      'label'       => t("Summary or trimmed with typo fixes"),
      'field types' => ['text_with_summary'],
      'settings'    => typomagic_defaults() + ['trim_length' => 600],
    ],
  ];
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function typomagic_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $settings = $instance['display'][$view_mode]['settings'] ?? [];

  // Module could be disabled, we have no explicit dependency.
  if (function_exists('text_field_formatter_settings_form')) {
    $element = text_field_formatter_settings_form($field, $instance, $view_mode, $form, $form_state);
  } else{
    $element = [];
  }

  $element += typomagic_form($settings);

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function typomagic_field_formatter_settings_summary($field, $instance, $view_mode) {
  $settings = $instance['display'][$view_mode]['settings'] ?? [];
  $summary = [];

  // Module could be disabled, we have no explicit dependency.
  if (function_exists('text_field_formatter_settings_summary')) {
    if ($text = text_field_formatter_settings_summary($field, $instance, $view_mode)) {
      $summary[] = $text;
    }
  }

  if ($settings['header_enable']) {
    $summary[] = t("Headers start at @tag", ['@tag' => 'H'.($settings['header_delta'] + 1)]);
  }
  if ($settings['jolitypo_enable']) {
    $summary[] = t("Locale is @locale", ['@locale' => $settings['jolitypo_locale']]);
  }

  return implode(' ', $summary);
}

/**
 * Implements hook_field_formatter_view().
 */
function typomagic_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element    = [];

  $settings   = $display['settings'] + typomagic_defaults();
  $withFormat = $instance['settings']['text_processing'];
  $useSummary = 'typomagic_summary_or_trimmed' === $display['type'];
  $doTrim     = $useSummary || 'typomagic_trimmed' === $display['type'];

  foreach ($items as $delta => $item) {
    $reallyDoTrim = $doTrim;

    if ($useSummary && !empty($item['summary'])) {
      $output = _text_sanitize($instance, $langcode, $item, 'summary');
      $reallyDoTrim = false; // Do not trim summaries.
    } else {
      $output = _text_sanitize($instance, $langcode, $item, 'value');
    }

    if ($reallyDoTrim) {
      $output = text_summary($output, $withFormat ? $item['format'] : null, $settings['trim_length']);
    }

    $output = typomagic_run($output, $settings);

    $element[$delta] = array('#markup' => $output);
  }

  return $element;
}
