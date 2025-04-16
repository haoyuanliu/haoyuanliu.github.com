---
title: Sprint Boot 工程中HanLP配置路径BUG解决
categories: Java
tags:
  - Spring Boot
  - HanLP
  - Adapter
abbrlink: 40145
date: 2020-07-03 16:06:03
---

### 0、 摘要

在Spring Boot工程中使用HanLP工具，按照平常的配置，将根路径配置为`root=src/main/resources/HanLP/`始终加载不成功，总是显示<br>`Caused by: java.lang.IllegalArgumentException: 核心词典src/main/resources/HanLP/data/dictionary/CoreNatureDictionary.txt加载失败`<br>的错误，然而平时常规的maven工程中这么用是没有问题的。

经过查阅源码，最终发现HanLP提供了IO适配器来解析路径，默认的适配器用的是`com.hankcs.hanlp.corpus.io.FileIOAdapter`，是基于普通文件系统的，我们通过自己定制一个IO适配器，并在配置文件中配置指定适配器的类型，就可以正常读取`resources`下的data了，这样避免了使用绝对路径，本地运行和服务器运行都比较方便！

<!--more-->

### 1、问题描述

按照常规Maven工程的方式配置hanlp的配置文件，如下所示：

```properties
#本配置文件中的路径的根目录，根目录+其他路径=完整路径（支持相对路径，请参考：https://github.com/hankcs/HanLP/pull/254）
#Windows用户请注意，路径分隔符统一使用/
#root=/Users/bayron/Desktop/tools/HanLP/
root=src/main/resources/HanLP/


#好了，以上为唯一需要修改的部分，以下配置项按需反注释编辑。

#核心词典路径
CoreDictionaryPath=data/dictionary/CoreNatureDictionary.txt
#2元语法词典路径
BiGramDictionaryPath=data/dictionary/CoreNatureDictionary.ngram.txt
#自定义词典路径，用;隔开多个自定义词典，空格开头表示在同一个目录，使用“文件名 词性”形式则表示这个词典的词性默认是该词性。优先级递减。
#所有词典统一使用UTF-8编码，每一行代表一个单词，格式遵从[单词] [词性A] [A的频次] [词性B] [B的频次] ... 如果不填词性则表示采用词典的默认词性。
CustomDictionaryPath=data/dictionary/custom/CustomDictionary.txt; 现代汉语补充词库.txt; 全国地名大全.txt ns; 人名词典.txt; 机构名词典.txt; 上海地名.txt ns;data/dictionary/person/nrf.txt nrf;
#停用词词典路径
CoreStopWordDictionaryPath=data/dictionary/stopwords.txt
#同义词词典路径
CoreSynonymDictionaryDictionaryPath=data/dictionary/synonym/CoreSynonym.txt
#人名词典路径
PersonDictionaryPath=data/dictionary/person/nr.txt
#人名词典转移矩阵路径
PersonDictionaryTrPath=data/dictionary/person/nr.tr.txt
#繁简词典根目录
tcDictionaryRoot=data/dictionary/tc
#HMM分词模型
HMMSegmentModelPath=data/model/segment/HMMSegmentModel.bin
#分词结果是否展示词性
ShowTermNature=true
#IO适配器，实现com.hankcs.hanlp.corpus.io.IIOAdapter接口以在不同的平台（Hadoop、Redis等）上运行HanLP
#默认的IO适配器如下，该适配器是基于普通文件系统的。
#IOAdapter=com.hankcs.hanlp.corpus.io.FileIOAdapter
#感知机词法分析器
#PerceptronCWSModelPath=data/model/perceptron/pku199801/cws.bin
#PerceptronPOSModelPath=data/model/perceptron/pku199801/pos.bin
#PerceptronNERModelPath=data/model/perceptron/pku199801/ner.bin
#CRF词法分析器
#CRFCWSModelPath=data/model/crf/pku199801/cws.txt
#CRFPOSModelPath=data/model/crf/pku199801/pos.txt
#CRFNERModelPath=data/model/crf/pku199801/ner.txt
#更多配置项请参考 https://github.com/hankcs/HanLP/blob/master/src/main/java/com/hankcs/hanlp/HanLP.java#L59 自行添加
```



可以正常解析配置文件并加载词典，并运行，但是迁移到SprintBoot工程之后，就会遇到如下错误：

```java
2020-07-03 11:05:04.984  WARN 29664 --- [pool-1-thread-1] HanLP                                    : 读取HanLP/data/dictionary/CoreNatureDictionary.txt.bin时发生异常java.io.FileNotFoundException: HanLP\data\dictionary\CoreNatureDictionary.txt.bin (系统找不到指定的路径。)
2020-07-03 11:05:04.984  WARN 29664 --- [pool-1-thread-1] HanLP                                    : 核心词典src/main/resources/HanLP/data/dictionary/CoreNatureDictionary.txt不存在！java.io.FileNotFoundException: src\main\resources\HanLP\data\dictionary\CoreNatureDictionary.txt (系统找不到指定的路径。)
Exception in thread "pool-1-thread-1" java.lang.ExceptionInInitializerError
	at com.hankcs.hanlp.seg.common.Vertex.newB(Vertex.java:455)
	at com.hankcs.hanlp.seg.common.WordNet.<init>(WordNet.java:73)
	at com.hankcs.hanlp.seg.Viterbi.ViterbiSegment.segSentence(ViterbiSegment.java:40)
	at com.hankcs.hanlp.seg.Segment.seg(Segment.java:573)
	at com.hankcs.hanlp.tokenizer.StandardTokenizer.segment(StandardTokenizer.java:50)
	at com.hankcs.hanlp.HanLP.segment(HanLP.java:632)
	at com.ict.mcg.model.HanLPChineseTokenizer.<init>(HanLPChineseTokenizer.java:57)
	at com.ict.mcg.model.HanLPTokenizerFactory.create(HanLPTokenizerFactory.java:18)
	at org.deeplearning4j.iterator.CnnSentenceDataSetIterator.tokenizeSentence(CnnSentenceDataSetIterator.java:158)
	at org.deeplearning4j.iterator.CnnSentenceDataSetIterator.loadSingleSentence(CnnSentenceDataSetIterator.java:110)
	at com.ict.mcg.model.CNNTextClass.predict(CNNTextClass.java:465)
	at com.ict.mcg.model.CNNTextClass.predict(CNNTextClass.java:458)
	at com.ict.mcg.model.CNNContentClassifier.run_predict(CNNContentClassifier.java:31)
	at com.ict.mcg.thrift.service.ClassifyService.doClassification(ClassifyService.java:22)
	at com.ict.mcg.thrift.bean.ClassifyProcessor$Processor$doClassification.getResult(ClassifyProcessor.java:155)
	at com.ict.mcg.thrift.bean.ClassifyProcessor$Processor$doClassification.getResult(ClassifyProcessor.java:135)
	at org.apache.thrift.ProcessFunction.process(ProcessFunction.java:38)
	at org.apache.thrift.TBaseProcessor.process(TBaseProcessor.java:38)
	at org.apache.thrift.server.TThreadPoolServer$WorkerProcess.run(TThreadPoolServer.java:313)
	at java.util.concurrent.ThreadPoolExecutor.runWorker(ThreadPoolExecutor.java:1149)
	at java.util.concurrent.ThreadPoolExecutor$Worker.run(ThreadPoolExecutor.java:624)
	at java.lang.Thread.run(Thread.java:748)
Caused by: java.lang.IllegalArgumentException: 核心词典src/main/resources/HanLP/data/dictionary/CoreNatureDictionary.txt加载失败
	at com.hankcs.hanlp.dictionary.CoreDictionary.<clinit>(CoreDictionary.java:44)
	... 22 more

```



### 2、将路径配置为绝对路径

如果将上面配置文件中的路径配置为如下的绝对路径：

```properties
root=F:\\project\\ClassifyRPC\\ClassifyServer\\src\\main\\resources\\HanLP\\
```

经过测试可以验证，HanLP的配置文件和词典可以正常解析加载，没有问题！



### 3、 将路径配置为<u>classpath:</u>开头的

```properties
root=classpath:/resources/HanLP/
```

结果还是报错：

```java
2020-07-03 11:23:41.749  WARN 29840 --- [pool-1-thread-1] HanLP                                    : 读取classpath:/resources/HanLP/data/dictionary/CoreNatureDictionary.txt.bin时发生异常java.io.FileNotFoundException: classpath:\resources\HanLP\data\dictionary\CoreNatureDictionary.txt.bin (文件名、目录名或卷标语法不正确。)
2020-07-03 11:23:41.750  WARN 29840 --- [pool-1-thread-1] HanLP                                    : 核心词典classpath:/resources/HanLP/data/dictionary/CoreNatureDictionary.txt不存在！java.io.FileNotFoundException: classpath:\resources\HanLP\data\dictionary\CoreNatureDictionary.txt (文件名、目录名或卷标语法不正确。)
Exception in thread "pool-1-thread-1" java.lang.ExceptionInInitializerError
	at com.hankcs.hanlp.seg.common.Vertex.newB(Vertex.java:455)
	at com.hankcs.hanlp.seg.common.WordNet.<init>(WordNet.java:73)
	at com.hankcs.hanlp.seg.Viterbi.ViterbiSegment.segSentence(ViterbiSegment.java:40)
	at com.hankcs.hanlp.seg.Segment.seg(Segment.java:573)
	at com.hankcs.hanlp.tokenizer.StandardTokenizer.segment(StandardTokenizer.java:50)
	at com.hankcs.hanlp.HanLP.segment(HanLP.java:632)
	at com.ict.mcg.model.HanLPChineseTokenizer.<init>(HanLPChineseTokenizer.java:57)
	at com.ict.mcg.model.HanLPTokenizerFactory.create(HanLPTokenizerFactory.java:18)
	at org.deeplearning4j.iterator.CnnSentenceDataSetIterator.tokenizeSentence(CnnSentenceDataSetIterator.java:158)
	at org.deeplearning4j.iterator.CnnSentenceDataSetIterator.loadSingleSentence(CnnSentenceDataSetIterator.java:110)
	at com.ict.mcg.model.CNNTextClass.predict(CNNTextClass.java:465)
	at com.ict.mcg.model.CNNTextClass.predict(CNNTextClass.java:458)
	at com.ict.mcg.model.CNNContentClassifier.run_predict(CNNContentClassifier.java:31)
	at com.ict.mcg.thrift.service.ClassifyService.doClassification(ClassifyService.java:22)
	at com.ict.mcg.thrift.bean.ClassifyProcessor$Processor$doClassification.getResult(ClassifyProcessor.java:155)
	at com.ict.mcg.thrift.bean.ClassifyProcessor$Processor$doClassification.getResult(ClassifyProcessor.java:135)
	at org.apache.thrift.ProcessFunction.process(ProcessFunction.java:38)
	at org.apache.thrift.TBaseProcessor.process(TBaseProcessor.java:38)
	at org.apache.thrift.server.TThreadPoolServer$WorkerProcess.run(TThreadPoolServer.java:313)
	at java.util.concurrent.ThreadPoolExecutor.runWorker(ThreadPoolExecutor.java:1149)
	at java.util.concurrent.ThreadPoolExecutor$Worker.run(ThreadPoolExecutor.java:624)
	at java.lang.Thread.run(Thread.java:748)
Caused by: java.lang.IllegalArgumentException: 核心词典classpath:/resources/HanLP/data/dictionary/CoreNatureDictionary.txt加载失败
	at com.hankcs.hanlp.dictionary.CoreDictionary.<clinit>(CoreDictionary.java:44)
	... 22 more

```



### 4、原因探究

#### 4.1 hanlp源码读取root路径的逻辑：

![image-20200703121603922](https://raw.githubusercontent.com/haoyuanliu/blog_pic/master/2020-07-03/image-20200703121603922.png)

在HanLP.class源码中，我们看到根目录root就是直接读取我们配置文件中的路径，并且兼容windows文件系统路径，字典等路径就是根据这个root路径进行拼装，比如我们配置root为`src/main/resources/HanLP/`，则后续路径都是以`src/main/resources/HanLP/`开头的，读取失败应该是因为代码中没有取到这个相对路径的文件；



#### 4.2 文件加载逻辑

![image-20200703122108593](https://raw.githubusercontent.com/haoyuanliu/blog_pic/master/2020-07-03/image-20200703122108593.png)

在CoreDictionary.java中的42行进行了词典的加载，这里出错，从而导致了上述错误；



![image-20200703133737964](https://raw.githubusercontent.com/haoyuanliu/blog_pic/master/2020-07-03/image-20200703133737964.png)

继续向下追踪，在IOUtil.java中，首先判断了IOAdapter是否为null，如果为null，则调用系统的FileInputStream，其中调用了`new File()`操作，对于相对路径的文件，确实会打开失败！

![image-20200703133825157](https://raw.githubusercontent.com/haoyuanliu/blog_pic/master/2020-07-03/image-20200703133825157.png)



那么如果`IOAdapter`不为null的话，会调用`IOAdapter.open(path)`，`IOAdapter`的实现类`ResourceIOAdapter`中的open函数如下所示：

![image-20200703134140075](https://raw.githubusercontent.com/haoyuanliu/blog_pic/master/2020-07-03/image-20200703134140075.png)

由上面代码可以看到这时就会去Resource中去寻找配置文件，我们尝试将`IOAdapter`激活，使其不为null；



#### 4.3 激活IOAdapter



##### 4.3.1 IIOAdapter适配器接口及示例

`IOAdapter`其实是接口`IIOAdapter`的一个实例，其中`IIOAdapter`接口默认有两个实现，分别是`FileIOAdapter`和`ResourceIOAdapter`；

![image-20200703144659226](https://raw.githubusercontent.com/haoyuanliu/blog_pic/master/2020-07-03/image-20200703144659226.png)



其中`FileIOAdapter`的代码逻辑如下，他是基于普通文件系统进行处理的：

```java
/*
 * <summary></summary>
 * <author>Hankcs</author>
 * <email>me@hankcs.com</email>
 * <create-date>2016-09-07 PM4:42</create-date>
 *
 * <copyright file="FileIOAdapter.java" company="码农场">
 * Copyright (c) 2008-2016, 码农场. All Right Reserved, http://www.hankcs.com/
 * This source is subject to Hankcs. Please contact Hankcs to get more information.
 * </copyright>
 */
package com.hankcs.hanlp.corpus.io;

import java.io.*;

/**
 * 基于普通文件系统的IO适配器
 *
 * @author hankcs
 */
public class FileIOAdapter implements IIOAdapter
{
    @Override
    public InputStream open(String path) throws FileNotFoundException
    {
        return new FileInputStream(path);
    }

    @Override
    public OutputStream create(String path) throws FileNotFoundException
    {
        return new FileOutputStream(path);
    }
}

```



`ResourceIOAdapter`听上去特别像我们需要的文件处理适配器，具体代码如下：

```java
/*
 * <author>Hankcs</author>
 * <email>me@hankcs.com</email>
 * <create-date>2016-09-24 AM8:34</create-date>
 *
 * <copyright file="ResourceIOAdapter.java" company="码农场">
 * Copyright (c) 2016, 码农场. All Right Reserved, http://www.hankcs.com/
 * This source is subject to Hankcs. Please contact Hankcs to get more information.
 * </copyright>
 */
package com.hankcs.hanlp.corpus.io;

import java.io.*;

/**
 * 从jar包资源读取文件的适配器
 * @author hankcs
 */
public class ResourceIOAdapter implements IIOAdapter
{
    @Override
    public InputStream open(String path) throws IOException
    {
        return IOUtil.isResource(path) ? IOUtil.getResourceAsStream("/" + path) : new FileInputStream(path);
    }

    @Override
    public OutputStream create(String path) throws IOException
    {
        if (IOUtil.isResource(path)) throw new IllegalArgumentException("不支持写入jar包资源路径" + path);
        return new FileOutputStream(path);
    }
}

```



很明显，`ResourceIOAdapter`是为了处理从jar包资源读取文件的适配器；

##### 4.3.2 自己定制IIOAdapter适配器

既然现有的适配器都不能满足我们的需要，那么我们就自己定制一个适配器，代码如下：

```java
package com.ict.mcg.config;

import com.hankcs.hanlp.corpus.io.IIOAdapter;
import org.springframework.core.io.ClassPathResource;

import java.io.*;

public class ResourceFileIoAdapter implements IIOAdapter {
    @Override
    public InputStream open(String path) throws IOException {
        ClassPathResource resource = new ClassPathResource(path);
        InputStream is = new FileInputStream(resource.getFile());
        return is;
    }

    @Override
    public OutputStream create(String path) throws IOException {
        ClassPathResource resource = new ClassPathResource(path);
        OutputStream os = new FileOutputStream(resource.getFile());
        return os;
    }
}

```

在代码中加入上述适配器类，我们就不需要指定hanlp词典等绝对路径了，只需要将HanLP.data放到项目的resource下，并指定IOAdapter实例的类别，就可以愉快的开发了！

具体配置如下：

```properties
root=HanLP/
IOAdapter=com.ict.mcg.config.ResourceFileIoAdapter
```

