#include "common/runtime/runtime_features.h"

namespace Envoy {
namespace Runtime {

// Add additional features here to enable the new code paths by default.
//
// Per documentation in CONTRIBUTING.md is expected that new high risk code paths be guarded
// by runtime feature guards, i.e
//
// if (Runtime::runtimeFeatureEnabled("envoy.reloadable_features.my_feature_name")) {
//   [new code path]
// else {
//   [old_code_path]
// }
//
// Runtime features are false by default, so the old code path is exercised.
// To make a runtime feature true by default, add it to the array below.
// New features should be true-by-default for an Envoy release cycle before the
// old code path is removed.
//
// If issues are found that require a runtime feature to be disabled, it should be reported
// ASAP by filing a bug on github. Overriding non-buggy code is strongly discouraged to avoid the
// problem of the bugs being found after the old code path has been removed.
constexpr const char* runtime_features[] = {
    // Enabled
    "envoy.reloadable_features.test_feature_true",
    "envoy.reloadable_features.strict_header_validation",
    "envoy.reloadable_features.buffer_filter_populate_content_length",
    "envoy.reloadable_features.outlier_detection_support_for_grpc_status",
    "envoy.reloadable_features.connection_header_sanitization",
    "envoy.reloadable_features.strict_authority_validation",
    "envoy.reloadable_features.reject_unsupported_transfer_encodings",
    "envoy.reloadable_features.strict_method_validation",
};

// This is a section for officially sanctioned runtime features which are too
// high risk to be enabled by default. Examples where we have opted to land
// features without enabling by default are swapping the underlying buffer
// implementation or the HTTP/1.1 codec implementation. Most features should be
// enabled by default.
//
// When features are added here, there should be a tracking bug assigned to the
// code owner to flip the default after sufficient testing.
constexpr const char* disabled_runtime_features[] = {
    // Sentinel and test flag.
    "envoy.reloadable_features.test_feature_false",
    // Should be removed as part of https://github.com/envoyproxy/envoy/issues/8993
    "envoy.reloadable_features.http2_protocol_options.stream_error_on_invalid_http_messaging",
};

// This is a list of configuration fields which are disallowed by default in Envoy
//
// By default, use of proto fields marked as deprecated in their api/.../*.proto file will result
// in a logged warning, so that Envoy users have a warning that they are using deprecated fields.
//
// During the Envoy release cycle, the maintainer team runs a script which will upgrade currently
// deprecated features to be disallowed (adding them to the list below) at which point use of said
// feature will cause a hard-failure (ProtoValidationException) instead of a logged warning.
//
// The release cycle after a feature has been marked disallowed, it is officially removable, and
// the maintainer team will run a script creating a tracking issue for proto and code clean up.
constexpr const char* disallowed_features[] = {
    // Acts as both a test entry for deprecated.proto and a marker for the Envoy
    // deprecation scripts.
    "envoy.deprecated_features.deprecated.proto:is_deprecated_fatal",
    // 1.10.0
    "envoy.deprecated_features.config_source.proto:UNSUPPORTED_REST_LEGACY",
    "envoy.deprecated_features.ext_authz.proto:use_alpha",
    "envoy.deprecated_features.fault.proto:type",
    "envoy.deprecated_features.route.proto:enabled",
    "envoy.deprecated_features.route.proto:runtime_key",
    // 1.11.0
    "envoy.deprecated_features.bootstrap.proto:runtime",
    "envoy.deprecated_features.redis_proxy.proto:catch_all_cluster",
    "envoy.deprecated_features.redis_proxy.proto:cluster",
    "envoy.deprecated_features.server_info.proto:max_obj_name_len",
    "envoy.deprecated_features.server_info.proto:max_stats",
    "envoy.deprecated_features.v1_filter_json_config",
};

RuntimeFeatures::RuntimeFeatures() {
  for (auto& feature : disallowed_features) {
    disallowed_features_.insert(feature);
  }
  for (auto& feature : runtime_features) {
    enabled_features_.insert(feature);
  }
  for (auto& feature : disabled_runtime_features) {
    disabled_features_.insert(feature);
  }
}

} // namespace Runtime
} // namespace Envoy
