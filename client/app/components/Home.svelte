<script lang="ts">
  import { Template } from "svelte-native/components";

  let message: string = "Graph placeholder";
  function onButtonTap() {}

  const domains = ["joelbosch.nl", "product-in-perspective.com"];
</script>

<page>
  <actionBar title="Stats" />
  <stackLayout>
    <listView class="navigation part" items={domains}>
      <Template let:item>
        <label text={item} />
      </Template>
    </listView>
    <listView class="navigation part" items={domains}>
      <Template let:item>
        <label text={item} />
      </Template>
    </listView>
    <listView class="navigation part" items={domains}>
      <Template let:item>
        <label text={item} />
      </Template>
    </listView>
    <label class="graph part">
      <formattedString>
        <span text="Graph placeholder" />
      </formattedString>
    </label>
    <label class="table part">
      <formattedString>
        <span text="Table placeholder" />
      </formattedString>
    </label>
  </stackLayout>
</page>

<style>
  .part {
    font-size: 20;
    text-align: center;
    vertical-align: center;
    width: 100%;
  }
  .navigation {
    height: 7%;
    background-color: navy;
  }
  .graph {
    height: 30%;
    background-color: deeppink;
  }
  .table {
    height: 55%;
    color: black;
    background-color: whitesmoke;
  }
</style>
