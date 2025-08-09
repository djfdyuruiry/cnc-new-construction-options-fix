using System;
using System.IO;
using System.Net.Http;
using System.Threading;
using System.Threading.Tasks;

using DiscUtils.Iso9660;
using InstallShieldExtractor;
using SharpCompress.Common;
using SharpCompress.Readers;

public partial class Example
{
  private static async Task FetchCncIsoIfMissing(string zipSource, string cachePath, string isoFileName)
  {
    if (File.Exists(Path.Join(cachePath, isoFileName)))
    {
      return;
    }

    Console.WriteLine($"Downloading C&C 95 GDI ISO from {zipSource}");

    using var client = new HttpClient { Timeout = Timeout.InfiniteTimeSpan };
    using var response = await client.GetAsync(zipSource, HttpCompletionOption.ResponseHeadersRead);

    response.EnsureSuccessStatusCode();

    Console.WriteLine($"HTTP response started");

    using var responseStream = await response.Content.ReadAsStreamAsync();
    using var zipReader = ReaderFactory.Open(responseStream);

    while (zipReader.MoveToNextEntry())
    {
      if (zipReader.Entry.Key == isoFileName)
      {
        Console.WriteLine($"Found ISO in ZIP download stream: {isoFileName}");
        zipReader.WriteEntryToDirectory(cachePath, new ExtractionOptions() { Overwrite = true });
      }

      break;
    }
  }

  static async Task Main(string[] args)
  {
    string cachePath = Path.Join(AppContext.BaseDirectory, ".cache");

    Directory.CreateDirectory(cachePath);

    var isoFileName = "CNC95_GDI.iso";
    var isoPath = Path.Join(cachePath, isoFileName);

    await FetchCncIsoIfMissing("https://bigdownloads.cnc-comm.com/cnc1/CNC95_GDI.zip", cachePath, isoFileName);

    using var isoStream = File.Open(isoPath, FileMode.Open);
    using var iso = new CDReader(isoStream, true);

    // mix file
    Console.WriteLine("Extracting file from C&C ISO: CONQUER.MIX");

    using var conquerMixInStream = iso.OpenFile(@"CONQUER.MIX", FileMode.Open);
    using var conquerMixOutStream = File.Open(Path.Join(cachePath, "CONQUER.MIX"), FileMode.Create);

    conquerMixInStream!.CopyTo(conquerMixOutStream);

    // install shield archive
    Console.WriteLine(@"Extracting C&C installer archive file from ISO: install\setup.z");
    using var setupStream = iso.OpenFile(@"install\setup.z", FileMode.Open);

    using var setupPackage = new InstallShieldPackage(setupStream, "setup.z");

    foreach (var package in setupPackage.Contents)
    {
      if (package.EndsWith("CCLOCAL.MIX"))
      {
        Console.WriteLine("Extracting file from C&C installer archive: CCLOCAL.MIX");

        using var cclocalStream = File.Open(Path.Join(cachePath, "CCLOCAL.MIX"), FileMode.Create);
        using var packageFileStream = setupPackage.GetStream(package);

        packageFileStream!.CopyTo(cclocalStream);
      }
    }

    // TODO: Extract installer background to use in Avalonia app
    // Console.WriteLine("Extracting C&C setup background image from ISO: setup.bmp");
    // using var fileStream = iso.OpenFile(@"setup.bmp", FileMode.Open);
    // this.Get<Image>("BackgroundImage").Source = Bitmap.DecodeToHeight(fileStream, 480);
  }
}