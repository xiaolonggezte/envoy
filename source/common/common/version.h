#pragma once

#include <string>

#include "envoy/config/core/v3alpha/base.pb.h"

#include "common/common/version_number.h"
#include "common/singleton/const_singleton.h"

namespace Envoy {

class VersionInfoTestPeer;

/**
 * Wraps compiled in code versioning.
 */
class VersionInfo {
public:
  // Repository revision (e.g. git SHA1).
  static const std::string& revision();
  // Repository status (e.g. clean, modified).
  static const std::string& revisionStatus();
  // Repository information and build type.
  static const std::string& version();

  static const envoy::config::core::v3alpha::BuildVersion& buildVersion();

private:
  friend class Envoy::VersionInfoTestPeer;
  // RELEASE or DEBUG
  static const std::string& buildType();
  static const std::string& sslVersion();
  static envoy::config::core::v3alpha::BuildVersion makeBuildVersion(const char* version);
};

class BuildVersionMetadata {
public:
  // Type of build: RELEASE or DEBUG
  const std::string BuildType = "build.type";
  // Build label from the VERSION file
  const std::string BuildLabel = "build.label";
  // Version of the SSL implementation
  const std::string SslVersion = "ssl.version";
  // SCM revision of the source tree
  const std::string RevisionSHA = "revision.sha";
  // SCM status of the source tree
  const std::string RevisionStatus = "revision.status";
};

using BuildVersionMetadataKeys = ConstSingleton<BuildVersionMetadata>;

} // namespace Envoy
